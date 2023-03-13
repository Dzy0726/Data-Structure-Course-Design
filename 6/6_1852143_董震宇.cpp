#include <iostream>
using namespace std;

//家庭成员结构体
struct FamilyMember
{
    string name;//成员姓名
    int child_num;//孩子的个数
    FamilyMember * brother_pre;//前一个兄弟姐妹
    FamilyMember * brother_next;//后一个兄弟姐妹
    FamilyMember * father;//父亲节点
    FamilyMember * child;//孩子节点
};

//族谱 操作类
class FamilyTree
{
    
public:
    FamilyTree();//构造函数
    ~FamilyTree();//析构函数
    void Build_Ancestor();//建立祖先
    void Develop_Family();//完善家庭
    void Add_Member();//增加成员
    void Divorce_Member();//解散局部家庭
    void Change_Name();//修改成员信息
    FamilyMember * Find_Member(string name,FamilyMember * member);//查找家庭成员
    FamilyMember * Member_Create();//新建家庭成员节点
    void Show_Child(FamilyMember * father);//输出所有父节点的子节点
    
private:
    FamilyMember * ancestor;//祖先节点
};

//构造函数 构造祖先节点
FamilyTree::FamilyTree()
{
    ancestor = new FamilyMember;
    ancestor->name = "";
    ancestor->brother_pre = NULL;
    ancestor->brother_next = NULL;
    ancestor->father = NULL;
    ancestor->child = NULL;
}

FamilyTree::~FamilyTree()
{
    
}

//新建家庭成员
FamilyMember * FamilyTree::Member_Create()
{
    FamilyMember * p = new FamilyMember;
    p->name = "";
    p->father = NULL;
    p->child = NULL;
    p->brother_pre = NULL;
    p->brother_next = NULL;
    return p;
}

//查找名为name的家庭成员是否存在
FamilyMember * FamilyTree::Find_Member(string name, FamilyMember * member)
{
    FamilyMember * p = member,*temp = p,*brother = NULL;
    if(p->name == name)//如果传入的member就是要查找的人,则返回member
    {
        return p;
    }
    while (temp->brother_next)//如果member不是,递归查找member的兄弟
    {
        brother = Find_Member(name, temp->brother_next);//递归找完所有兄弟 还没有找到的话就从最后一个兄弟的儿子倒着往回找
        if(brother)
        {
            return brother;
        }
        temp = temp->brother_next;
    }
    temp = p;
    if(temp->child)//从孩子倒着往回找
    {
        brother = Find_Member(name, temp->child);
    }
    return brother;
}

void FamilyTree::Build_Ancestor()
{
    cout << "首先建立一个家谱!" << endl;
    cout << "请输入祖先的姓名是:";
    cin >> ancestor->name;
    cout << "此家谱的祖先是:" << ancestor->name << endl;
}

//输出父节点的所有子女信息
void FamilyTree::Show_Child(FamilyMember * father)
{
    if(father -> child_num == 0)
    {
        cout << "没有后代!" << endl;
        return;
    }
    FamilyMember * p = father->child;
    cout << father->name <<"的第一代子孙为:";
    for(int i = 0;i < father->child_num;i++)
    {
        cout << p->name << " ";
        if(p->brother_next != NULL)
        {
            p = p->brother_next;
        }
    }
}

//操作A 完善家庭
void FamilyTree::Develop_Family()
{
start :cout << "请输入要建立家庭的人的姓名:";
    string name;
    cin >> name;
    FamilyMember *p = Find_Member(name, ancestor);
    if(p == NULL)
    {
        cout << "查无此人!" << "请检查输入!" << endl;
        goto start;
    }
    if(p->child != NULL)
    {
        cout << "已经建立过家庭!" << "请检查输入!" << endl;
        goto start;
    }
    cout << "请输入" << p->name << "儿女人数:";
    cin >> p->child_num;
    if(p->child_num == 0)
    {
        cout << p->name << "没有儿女!" << endl;
        return;
    }
    cout << "请依次输入" << p->name << "的儿女的姓名:";
    p->child = Member_Create();
    FamilyMember * temp = p->child;
    cin >> temp->name;
    temp->father = p;// temp （指向头结点的指针，类似于head是头结点 要有p指向头结点 操作p）
    for(int i = 0;i < p->child_num-1;i++)//循环创建所有子女节点并用 循环链表 连接
    {
        FamilyMember * brother = Member_Create();
        cin >> brother->name;
        brother->father = p;
        brother->brother_pre = temp;
        temp->brother_next = brother;
        temp = temp->brother_next;
    }
    Show_Child(p);
}

//操作B 添加家庭成员
void FamilyTree::Add_Member()
{
start:string name;
    cout << "请输入要添加儿子或女儿的人的姓名:";
    cin >> name;
    FamilyMember * p = Find_Member(name, ancestor);
    if(p == NULL)
    {
        cout << "查无此人!请检查输入!" << endl;
        goto start;
    }
    cout << "请输入" << p->name << "新添加的儿子或女儿的姓名:";
    FamilyMember * child = Member_Create();
    if(p->child == NULL)
    {
        child->father = p;
        p->child = child;
        cin >> child->name;
        p->child_num = 1;
    }
    else
    {
        FamilyMember * q = p->child;
        for(int i = 0;i < p->child_num-1;i++)
        {
            q = q->brother_next;
        }
        cin >> child->name;
        child->father = p;
        q->brother_next = child;
        child->brother_pre = q;
        p->child_num++;
    }
    Show_Child(p);
}

//操作C 解散局部家庭
void FamilyTree::Divorce_Member()
{
start:cout << "请输入要解散家庭的人的姓名:";
    string name;
    cin >> name;
    FamilyMember * p = Find_Member(name, ancestor);
    if(p == NULL)
    {
        cout << "查无此人!请检查输入!" << endl;
        goto start;
    }
    if(p->child == NULL)
    {
        cout << p->name << "尚未成立家庭!";
        return;
    }
    if (p->brother_pre != NULL && p->brother_next != NULL)
    {
        p->brother_pre->brother_next = p->brother_next;
        p->brother_next->brother_pre = p->brother_pre;
    }
    else if (p->brother_pre != NULL && p->brother_next == NULL)
    {
        p->brother_pre->brother_next = NULL;
    }
    else if (p->brother_pre == NULL && p->brother_next != NULL)
    {
        p->father->child = p->brother_next;
        p->brother_next->brother_pre = NULL;
    }
    else
    {
        p->father->child = NULL;
    }
    p->father->child_num--;
    cout << "要解散家庭的人是:" << p->name << endl;
    Show_Child(p);
    delete p;
}

//操作D 更改家庭成员姓名
void FamilyTree::Change_Name()
{
 start: cout << "请输入要更改姓名的人的目前的姓名:";
    string name,old_name;
    cin >> name;
    FamilyMember * p = Find_Member(name, ancestor);
    if(p == NULL)
    {
        cout << "查无此人!请检查输入!" << endl;
        goto start;
    }
    old_name = p->name;
    cout << "请输入" << p->name << "更改后的姓名:";
    cin >> name;
    p->name = name;
    cout << old_name << "已更名为" << p->name;
}

int main()
{
    FamilyTree Family;
    cout << "**              家谱管理系统              **"<<endl;
    cout << "============================================" << endl;
    cout << "**           请选择要执行的操作：            **" << endl;
    cout << "**             A --- 完善家谱             **" << endl;
    cout << "**             B --- 添加家庭成员          **"<< endl;
    cout << "**             C --- 解散局部家庭          **" << endl;
    cout << "**             D --- 更改家庭成员姓名       **" << endl;
    cout << "**             E --- 退出程序              **" << endl;
    cout << "============================================" << endl;
    char order;
    Family.Build_Ancestor();
    cout  << "请选择要执行的操作：";
    cin >> order;
    while (order != 'E'){
        switch (order){
        case 'A':
            Family.Develop_Family();
            break;
        case 'B':
            Family.Add_Member();
            break;
        case 'C':
            Family.Divorce_Member();
            break;
        case 'D':
            Family.Change_Name();
            break;
        default:
            cout << "请输入正确的命令";
            break;
        }
        cout << endl << "请选择要执行的操作：";
        cin >> order;
    }
    return 0;
}
