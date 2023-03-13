//
//  main.cpp
//  Cpp test
//
//  Created by 董震宇 on 2019/9/25.
//  Copyright © 2019 董震宇. All rights reserved.
//
#include <iostream>

using namespace std;


//===============================新建Student类================================//
//=============================成员变量为考生信息===============================//
class Student
{
    //======================对于系统的操作类为其友元=============================//
    friend class Operate;
    
public:
    string num;                  //考号
    string sex;               //性别
    string name;              //姓名
    string age;                  //年龄
    string subject;           //报考类别
    Student * next;           //指向下一节点
    
    Student();                //构造函数
};


//===============================新建Operate类===============================//
//============================成员变量为各种操作函数===========================//
class Operate
{
public:
    void Create(Operate &n);    //创建系统
    void Find(Operate &n);      //查找
    void Insert(Operate &n);    //插入
    void Change(Operate &n);    //修改
    void Delete(Operate &n);    //删除
    void Print(Operate &n);     //输出
    int Length(Operate &n);     //长度
    
    Operate();                  //构造函数
    
    Student *head;              //头结点
};


//======================Student类的构造函数,初始化结点数据=====================//
Student::Student()
{
    num = '0';
    sex = '\0';
    name = '\0';
    age = '0';
    subject = '\0';
    next = NULL;
}


//======================Operate类的构造函数,初始化首节点======================//
Operate::Operate()
{
    head = NULL;
}

//============================判断输入是否合法==============================//
bool Is_int(string num)
{
    unsigned long len = num.length();
    for(int i = 0;i < len;i++)
    {
        if(num[i] < '0' || num[i] > '9')
        {
            return false;
        }
    }
    return true;
}

//================================创建考生信息==============================//
void Operate::Create(Operate &n)
{
b:    cout << "请输入考生人数：";
    int m;
    cin >> m;
    if(!(m >= 1))
    {
        cout << "输入考生人数有误,请重新输入!" << endl;
        goto b;
    }
a:    cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！" << endl;
    Student *p,*s = nullptr;
    for(int i = 0;i < m;i++)
    {
        p = new Student;
        string num;
        cin >> num;
        
        string name;
        cin >> name;
        
        string sex;
        cin >> sex;
        
        string age;
        cin >> age;
        
        string type;
        cin >> type;
        
        bool isnum1 = Is_int(num);
        bool isnum2 = Is_int(age);
        if(isnum1 == true)
        {
            if(isnum2 == true)
            {
                p->num = num;
                p->name = name;
                p->sex = sex;
                p->subject = type;
                p->age = age;
            }
            else
            {
                cout << "请输入正确的年龄！" << endl;
                goto a;
            }
        }
        else
        {
            cout << "请输入正确的考号！" << endl;
            goto a;
        }
        
        if(i == 0)
        {
            n.head = p;
            s = n.head;
        }
        else
        {
            s->next = p;
            s = p;
        }
    }
}


//================================输出考生信息==============================//
void Operate::Print(Operate &n)
{
    Student *p = n.head;
    cout << endl;
    cout << "考号" << "\t" << "姓名" << "\t" << "性别" << "\t" << "年龄" << "\t" << "报考类别" << endl;
    while(p->next)
    {
        cout << p->num << "\t" << p->name << "\t" << p->sex << "\t" << p->age << "\t" << p->subject << endl;
        p = p->next;
    }
    cout << p->num << "\t" << p->name << "\t" << p->sex << "\t" << p->age << "\t" << p->subject << endl;
}


//================================计算链表的长度==============================//
int Operate::Length(Operate &n)
{
    Student *p = n.head;
    int i = 0;
    while(p->next)
    {
        i++;
        p = p->next;
    }
    return i+1;
}


//================================插入考生信息==============================//
void Operate::Insert(Operate &n)
{
a:  cout << "请输入你要插入考生的位置:";
    int i;
    cin >> i;
    int j = Operate::Length(n);
    if(i > j || i == 0)
    {
        cout << "你要插入的位置不存在！请重新输入!" << endl;
        goto a;
    }
    else
    {
        Student *p,*s;
        p = new Student;
        s = n.head;
        b:cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别！" << endl;
        string num;
        cin >> num;
        
        string name;
        cin >> name;
        
        string sex;
        cin >> sex;
        
        string age;
        cin >> age;
        
        string type;
        cin >> type;
        
        bool isnum1 = Is_int(num);
        bool isnum2 = Is_int(age);
        if(isnum1 == true)
        {
            if(isnum2 == true)
            {
                p->num = num;
                p->name = name;
                p->sex = sex;
                p->subject = type;
                p->age = age;
            }
            else
            {
                cout << "请输入正确的年龄！" << endl;
                goto b;
            }
        }
        else
        {
            cout << "请输入正确的考号！" << endl;
            goto b;
        }
        
        if(i == 1)
        {
            p->next = n.head;
            n.head = p;
        }
        else
        {
            int a = 1;
            while (a != i - 1)
            {
                s = s->next;
                a++;
            }
            p->next = s->next;
            s->next = p;
        }
    }
}


//================================删除考生信息==============================//
void Operate::Delete(Operate &n)
{
    cout << "请输入要删除的考生的考号:";
    string num;
    cin >> num;
    Student *s;
    if(n.head->num == num)
        {
            s = n.head;
            n.head = n.head -> next;
            cout << "你删除的考生信息是:" << s->num << '\t' << s->name <<'\t' << s->sex << '\t' << s->age <<'\t' << s->subject << endl;
            delete s;
            return;
        }
    Student *p = n.head;
    while(p->next != NULL)
    {
        if (p->next->num == num)
        {
            auto q = p-> next;
            p->next = p->next->next;
            cout << "你删除的考生信息是:" << q->num << '\t' << q->name <<'\t' << q->sex << '\t' << q->age <<'\t' << q->subject << endl;
            delete q;
            return;
        }
        p = p->next;
    }
    if(p->next == nullptr)
    {
        cout << "要删除的考生不存在,请重新输入考号!"<< endl;
        Operate::Delete(n);
    }
}


//================================查找考生信息==============================//
void Operate::Find(Operate &n)
{
    cout << "请输入要查找的考生的考号:";
    string num;
    int i=1;
    cin >> num;
    Student *p = n.head;
    while(p)
    {
        if(p->num == num)
        {
            cout << p->num << "\t" << p->name << "\t" << p->sex << "\t" << p->age << "\t" << p->subject << endl;
            break;
        }
        else
        {
            p = p->next;
            i++;
        }
    }
    if(i > Operate::Length(n))
    {
        cout << "要查找的考生不存在,请重新输入考号!"<< endl;
        Operate::Find(n);
    }
}


//================================修改考生信息==============================//
void Operate::Change(Operate &n)
{
    cout << "请输入要修改信息的考生的考号:";
    string num;
    int i=1;
    cin >> num;
    Student *p = n.head;
    while(p)
    {
        if(p->num == num)
        {
            a:cout << "请依次输入修改后的考生的考号,姓名,性别,年龄以及报考类别!" << endl;
            string num;
            cin >> num;
            
            string name;
            cin >> name;
            
            string sex;
            cin >> sex;
            
            string age;
            cin >> age;
            
            string type;
            cin >> type;
            
            bool isnum1 = Is_int(num);
            bool isnum2 = Is_int(age);
            if(isnum1 == true)
            {
                if(isnum2 == true)
                {
                    p->num = num;
                    p->name = name;
                    p->sex = sex;
                    p->subject = type;
                    p->age = age;
                }
                else
                {
                    cout << "请输入正确的年龄！" << endl;
                    goto a;
                }
            }
            else
            {
                cout << "请输入正确的考号！" << endl;
                goto a;
            }
            break;
        }
        else
        {
            p = p->next;
            i++;
        }
    }
    if(i > Operate::Length(n))
    {
        cout << "要修改的考生不存在,请重新输入考号!"<< endl;
        Operate::Change(n);
    }
}



int main(int argc, const char * argv[])
{
a:    cout << "首先请建立考生信息系统！" << endl;
    Operate n;
    n.Create(n);
    n.Print(n);
    int i = -1;
    while(i)
    {
        cout << endl;
        cout << "请选择您要进行的操作(1为插入 2为删除 3为查找 4为修改 5为统计 0为取消操作)" << endl;
        cin >> i;
        switch (i)
        {
            case 1:
                n.Insert(n);
                n.Print(n);
                break;
            case 2:
                n.Delete(n);
                if(n.head == NULL)
                {
                    cout << endl << "考生信息系统中已无考生,请重新建立考生信息系统!" << endl << endl;
                    goto a;
                }
                else
                {
                    n.Print(n);
                }
                break;
            case 3:
                n.Find(n);
                n.Print(n);
                break;
            case 4:
                n.Change(n);
                n.Print(n);
                break;
            case 5:
                cout << "该系统考生人数为:" << n.Length(n) << endl;
                break;
            case  0:
                cout << "欢迎下次使用，再见！" << endl;
                return 0;
            default:
                cout << "该操作不存在，请输入正确操作！" << endl;
                break;
        }
    }
    return 0;
}
