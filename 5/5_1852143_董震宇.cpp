#include <iostream>
#define N 1001
using namespace std;
//创建队列类(不使用STL)
class Queue
{
public:
    int  rear;//队尾指针
    int  front[N];//存储队列元素
public:
    Queue();//构造函数
    ~Queue();//析构函数
    bool empty();//判断队列是否为空,若空则返回true
    void push(int x);//将元素x入队
    int getfront();//取队首元素
};

Queue::Queue()
{
    rear = 0;//队尾指针置0
}

Queue::~Queue()
{
    
}

bool Queue::empty()
{
    if(rear == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Queue::push(int x)
{
    front[rear] = x;
    rear++;//队尾指针后移
}

int  Queue::getfront()
{
    if(rear == 0)
    {
        return false;//若队列为空,则返回false
    }
    int x = front[0];//取队首元素
    for(int i = 0;i < rear-1;i++)//将所有元素统一前移一位 相当于stl中的pop操作
    {
        front[i] = front[i+1];
    }
    rear--;//队尾-1
    return x;
}


int main()
{
    Queue jishu;
    Queue oushu;
    int n,m;
    cin >> n;
    while (n--)
    {
        cin >> m;
        if(m % 2 == 0)//若读入数据为偶数
        {
            oushu.push(m);//入偶数队列
        }
        else
        {
            jishu.push(m);//为奇数 入奇数队列
        }
    }
    while(!jishu.empty() && !oushu.empty())//当奇偶队列都有元素时
    {
        cout << jishu.getfront() << " ";//输出两个奇数一个偶数(A窗口两个B窗口一个)
        cout << jishu.getfront() << " ";
        cout << oushu.getfront() << " ";
    }
    //若出现某一队列元素没有全部输出 分别讨论
    while(!jishu.empty())
    {
        if(jishu.rear != 1)
        {
            cout << jishu.getfront() << " ";
        }
        else
        {
            cout << jishu.getfront();//只剩最后一个元素 结尾没有空格
        }
    }
    while(!oushu.empty())
    {
        if(oushu.rear != 1)
        {
            cout << oushu.getfront() << " ";
        }
        else
        {
            cout << oushu.getfront();
        }
    }
    return 0;
}
