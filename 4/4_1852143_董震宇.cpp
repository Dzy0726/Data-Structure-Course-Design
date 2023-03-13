#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <stack>

using namespace std;

int Priority(char operation)
{
    //判断运算符优先级
    if(operation == '(') return 1;
    else if(operation ==  '+' || operation == '-') return 2;
    else if(operation ==  '*' || operation == '/' || operation == '%') return 3;
    else if(operation ==  '^') return 4;
    else return 5;
}

void Calculate(stack<int> &stack_num,char operation)
{
    int num_left,num_right,result;
    num_right = stack_num.top();
    stack_num.pop();
    if(stack_num.empty())
    {
        num_left = 0;
    }
    else
    {
        num_left = stack_num.top();
        stack_num.pop();
    }
    if(operation == '+')
    {
        result = num_left+num_right;
       // cout << "现在运算的是:" << num_left << operation << num_right << "=" << result << endl;
    }
    else if (operation == '-')
    {
        result = num_left-num_right;
       //cout << "现在运算的是:" << num_left << operation << num_right << "=" << result << endl;
    }
    else if (operation == '*')
    {
        result = num_left*num_right;
       // cout << "现在运算的是:" << num_left << operation << num_right << "=" << result << endl;
    }
    else if (operation ==  '/')
    {
        if(num_right != 0)
        {
            result = num_left/num_right;
            //cout << "现在运算的是:" << num_left << operation << num_right << "=" << result << endl;
        }
        else
        {
            cerr << "除数不能为零!请检查表达式输入!" << endl;
            exit(1);
        }
    }
    else if (operation == '%')
    {
        result = num_left%num_right;
        //cout << "现在运算的是:" << num_left << operation << num_right << "=" << result << endl;
    }
    else
    {
        result = pow(num_left, num_right);
        //cout << "现在运算的是:" << num_left << operation << num_right << "=" << result << endl;
    }
    stack_num.push(result);
}

int Calculator(string formular)
{
    stack<int> num_stack;
    stack<char> operator_stack;
    int i = 0,j;
    long length = formular.length();
    char temp_op;
    string temp_num;
    while (i<length)
    {
        //如果读入的是数字,继续读后面的字符,直到不是数字
        //将这个多位数暂存入temp_num,再用atoi强制转换为int,进数栈
        if(formular[i] >= '0' && formular[i] <= '9')
        {
            j = i;
            while(j < length && formular[j] >= '0' && formular[j] <= '9')
            {
                j++;
            }
            temp_num = formular.substr(i,j-i);
            num_stack.push(atoi(temp_num.c_str()));
            i = j;
        }
        //如果读入的是运算符
        else if(formular[i] == '+' ||formular[i] == '-' ||formular[i] == '*' ||formular[i] == '/' ||formular[i] == '%' ||formular[i] == '^' )
        {
            //先看符号栈是否为空,若符号栈为空,则此符号直接进栈
            if(operator_stack.empty())
            {
                operator_stack.push(formular[i]);
            }
            //如果符号栈不为空,当符号栈不为空时,取出栈顶元素,与当前运算符比较优先级,如果栈顶元素优先级高,则进行运算函数
            //如果优先级低,则跳出循环,将当前运算符入栈
            else
            {
                while (!operator_stack.empty())
                {
                    temp_op = operator_stack.top();
                    if(Priority(temp_op) >= Priority(formular[i]) && formular[i] != '^')
                    {
                        Calculate(num_stack, temp_op);
                        operator_stack.pop();
                    }
                    else if (Priority(temp_op) > Priority(formular[i]) && formular[i] == '^')
                    {
                        Calculate(num_stack, temp_op);
                        operator_stack.pop();
                    }
                    else break;
                }
                operator_stack.push(formular[i]);
            }
            i++;
        }
        else if (formular[i] == '=')//如果读入等号直接对现在的所有数栈符号栈进行运算并返回结果
        {
            while (!operator_stack.empty())
            {
                temp_op = operator_stack.top();
                Calculate(num_stack, temp_op);
                operator_stack.pop();
            }
            return num_stack.top();
        }
        else
        {   //如果读入的是左括号,直接入栈
            if(formular[i]  == '(')
            {
                operator_stack.push(formular[i]);
            }
            else//如果读入的不是以上符号,则排除出错的话只剩右括号
            {   //当栈顶不是左括号时,进行运算
                while (operator_stack.top() != '(')
                {
                    temp_op = operator_stack.top();
                    Calculate(num_stack, temp_op);
                    operator_stack.pop();//把当前运算符出栈
                }
                operator_stack.pop();//把左括号出栈
            }
            i++;
        }
    }
    //遍历完后如果栈不是空的,弹出所有元素
    while(!operator_stack.empty())
    {
        temp_op = operator_stack.top();
        Calculate(num_stack, temp_op);
        operator_stack.pop();
    }
    return num_stack.top();
}


int main()
{
start:  string formula = "";
    char a ;
    int result;
    cout << "请输入要计算的表达式:(以回车键结束)"<< endl;
    cin >> formula;
    
    //异常处理:
    string judge = "0123456789+-*/^%()=";
    long length = formula.length();
    int i=0,j=0;
    int count=0,left=0,right=0;
    for(i = 0;i < length;i++)
    {
        count = 0;
        for(j = 0;j < 18;j++)
        {
            if(formula[i] != judge[j])
            {
                count++;
            }
        }
        if(count == 19)
        {
            cerr << "表达式输入有误,请检查输入!" << endl;
            goto start;
        }
        if(formula[i] == '(') left++;
        if(formula[i] == ')') right++;
    }
    if(left != right)
    {
        cerr << "左右括号不匹配,请检查输入!" << endl;
        goto start;
    }
    
    //进行运算:
    result = Calculator(formula);
    cout << "结果是:" << result << endl;
 
    //循环运算:
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

