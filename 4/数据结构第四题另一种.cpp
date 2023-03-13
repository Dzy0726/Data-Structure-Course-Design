#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <stack>

using namespace std;

stack<char> postfixStack;

int Priority(char operation)
{
    //判断运算符优先级
    if(operation == '(') return 1;
    else if(operation ==  '+' || operation == '-') return 2;
    else if(operation ==  '*' || operation == '/' || operation == '%') return 3;
    else if(operation ==  '^') return 4;
    else if(operation == '#') return -1;
    else return 5;
}

string getPostfixExpression(string formular)
{
    stack<char> operatorStack;
    string postfix = "";
    long length = formular.length();
    int i = 0,j;
    char temp_op;
    string temp_num;
    while (i<length)
        {
            //如果读入的是数字,继续读后面的字符,直到不是数字
            //将这个多位数暂存入temp_num,再用atoi强制转换为int,进后缀表达式栈
            if(formular[i] >= '0' && formular[i] <= '9')
            {
                j = i;
                while(j < length && formular[j] >= '0' && formular[j] <= '9')
                {
                    j++;
                }
                postfix += formular.substr(i,j-i);
                postfix.push_back('#');//读取多位数字用井号分隔
                i = j;
            }
            //如果读入的是运算符
            else if(formular[i] == '+' ||formular[i] == '-' ||formular[i] == '*' ||formular[i] == '/' ||formular[i] == '%' ||formular[i] == '^' )
            {
                //先看符号栈是否为空,若符号栈为空,则此符号直接进栈
                if(operatorStack.empty())
                {
                    operatorStack.push(formular[i]);
                }
                //如果符号栈不为空,当符号栈不为空时,取出栈顶元素,与当前运算符比较优先级,如果栈顶元素优先级高,则入后缀表达式栈
                //如果优先级低,则跳出循环,将当前运算符入运算符栈
                else
                {
                    while (!operatorStack.empty())
                    {
                        temp_op = operatorStack.top();
                        if(Priority(temp_op) >= Priority(formular[i]) && formular[i] != '^')
                        {
                            postfix.push_back(temp_op);
                            operatorStack.pop();
                        }
                        else if (Priority(temp_op) > Priority(formular[i]) && formular[i] == '^')
                        {
                            postfix.push_back(temp_op);
                            operatorStack.pop();
                        }
                        else break;
                    }
                    operatorStack.push(formular[i]);
                }
                i++;
            }
            else if (formular[i] == '=')//如果读入等号直接对现在的所有数栈符号栈进行运算并返回结果
                   {
                       while(!operatorStack.empty())
                       {
                           temp_op = operatorStack.top();
                           postfix.push_back(temp_op);
                           operatorStack.pop();
                       }
                       return postfix;
                   }
            else
            {   //如果读入的是左括号,直接入栈
                if(formular[i]  == '(')
                {
                    operatorStack.push(formular[i]);
                }
                else//如果读入的不是以上符号,则排除出错的话只剩右括号
                {   //当栈顶不是左括号时,进行运算
                    while (operatorStack.top() != '(')
                    {
                        temp_op = operatorStack.top();
                        postfix.push_back(temp_op);
                        operatorStack.pop();//把当前运算符出栈
                    }
                    operatorStack.pop();//把左括号出栈
                }
                i++;
            }
        }
        //遍历完后如果栈不是空的,弹出所有元素
        while(!operatorStack.empty())
        {
            temp_op = operatorStack.top();
            postfix.push_back(temp_op);
            operatorStack.pop();
        }
    return postfix;
}

int Calculator(string postfix)
{
    cout << postfix << endl;
    stack<int> numStack;
    long length = postfix.length();
    int num_left,num_right,result;
    int j;
    string temp_num;
    for(int i = 0;i < length;i++)
    {
        if(postfix[i] >= '0' && postfix[i] <= '9')
        {
            j = i;
            while(j < length && postfix[j] >= '0' && postfix[j] <= '9')
            {
                j++;
            }
            temp_num = postfix.substr(i,j-i);
            numStack.push(atoi(temp_num.c_str()));
            i = j;
        }
        else if(postfix[i] != '#')
        {
            num_right = numStack.top();
            numStack.pop();
            num_left=numStack.top();
            numStack.pop();
            if(postfix[i] == '+')
            {
                    result = num_left+num_right;
                    cout << "现在运算的是:" << num_left << postfix[i] << num_right << "=" << result << endl;
                
            }
            else if (postfix[i] == '-')
            {
                result = num_left+num_right;
                cout << "现在运算的是:" << num_left << postfix[i] << num_right << "=" << result << endl;
            
            }
            else if (postfix[i] == '*')
            {
                result = num_left*num_right;
                cout << "现在运算的是:" << num_left << postfix[i] << num_right << "=" << result << endl;
            }
            else if (postfix[i] ==  '/')
            {
                if(num_right != 0)
                {
                    result = num_left/num_right;
                    cout << "现在运算的是:" << num_left << postfix[i] << num_right << "=" << result << endl;
                }
                else
                {
                    cerr << "除数不能为零!请检查表达式输入!" << endl;
                    exit(1);
                }
            }
            else if (postfix[i] == '%')
            {
                result = num_left%num_right;
                cout << "现在运算的是:" << num_left << postfix[i] << num_right << "=" << result << endl;
            }
            else if (postfix[i] == '^')
            {
                result = pow(num_left, num_right);
                cout << "现在运算的是:" << num_left << postfix[i] << num_right << "=" << result << endl;
            }
            else
            {
                cout << "表达式输入有误,请重新输入!" << endl;
                exit(5);
            }
            numStack.push(result);
        }
    }
        return numStack.top();
}


int main()
{
start:  string formular = "";
    char a ;
    int result;
    cout << "请输入要计算的表达式:"<< endl;
    cin >> formular;
    string ab = getPostfixExpression(formular);
    result = Calculator(ab);
    cout << "结果是:" << result << endl;
    
conti:    cout << "是否继续进行运算?(y/n)" << endl;
    cin >> a;
    if(a ==  'y')
    {
        goto start;
    }
    else if (a == 'n')
    {
        cout << "欢迎下次使用,再见!" << endl;
        exit(0);
    }
    else
    {
        cout << "输入有误,请重新输入!" << endl;
        goto conti;
    }
    return 0;
}
-2*(3+5)+2^3/4=
