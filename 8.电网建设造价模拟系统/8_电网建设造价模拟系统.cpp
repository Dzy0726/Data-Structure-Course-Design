#include <iostream>
#include <queue>
#define INFINITY 999 //设置无穷大
bool Exist = false;
using namespace std;

struct Vertex   //顶点的结构体
{
    int num;    //顶点的序号
    string name;//顶点的名字
};

struct Tree
{
    string head; //生成树边节点的头
    string tail; //生成树边节点的尾
    int cost;    //生成树边的权值
};

class MST
{

public:
    int ver_num;//图节点的个数
    Vertex *vertices;//顶点的结构体数组
    int **edge_value;//图中各条边的权值
    queue <Tree> MSTree;//创建一个结构体队列来输出最小生成树
    MST();//构造函数
    ~MST();//析构函数
    void createVertex();//创建顶点
    void showVertxe();//输出所有顶点
    void addEdge();//增加图的边c
    void showEdge();//输出图的邻接矩阵
    void createTree();//生成最小生成树
    void displayTree();//输出最小生成树
};

MST::MST()
{
    ver_num = 0;
}

MST::~MST()
{

}

void MST::createVertex()
{
    cout << "请输入顶点的个数:";
    cin >> ver_num;
    vertices = new Vertex[ver_num];
    cout << "请依次输入各顶点的名称:";
    for(int i = 0;i < ver_num;i++)
    {
        cin >> vertices[i].name;
        vertices[i].num = i;
    }
}

void MST::showVertxe()
{
    for(int i = 0;i < ver_num;i++)
    {
        cout << "第" << vertices[i].num << "个顶点为:" << vertices[i].name << endl;
    }
}

void MST::addEdge()
{
    edge_value = new int*[ver_num];
    for(int i = 0;i < ver_num;i++)
    {
        edge_value[i] = new int[ver_num];
    }
    for(int i = 0;i < ver_num;i++)
    {
        for(int j = 0;j < ver_num;j++)
        {
            edge_value[i][j] = INFINITY;
        }
    }
    string a,b;
    int a_num = -1,b_num = -1,value;
    for(int i = 0;i < ver_num*(ver_num-1)/2;i++)
    {
s:      cout << "请依次输入两个顶点及边:(如果两顶点间不存在边则输入权值为999)";
        cin >> a >> b >> value;
        for(int j = 0;j < ver_num;j++)
        {
            if(vertices[j].name == a)
            {
                a_num = j;
            }
            else if(vertices[j].name == b)
            {
                b_num = j;
            }
        }
        if(a_num == -1 || b_num == -1 || a_num == b_num)
        {
            cout << "输入顶点有误!请重新输入!" << endl;
            goto s;
        }
        else
        {
            edge_value[a_num][b_num] = value;
            edge_value[b_num][a_num] = value;
        }
    }
}

void MST::showEdge()
{
    for(int i = 0;i < ver_num;i++)
    {
        for(int j = 0;j < ver_num;j++)
        {
            cout << edge_value[i][j] << "  ";
        }
        cout << endl;
    }
}

void MST::createTree()
{
    int *lowcost = new int[ver_num];//生成树顶点集合内顶点到生成树外各顶点的各边上的当前最小权值
    int *nearvex = new int[ver_num];//生成树顶点集合外各顶点距离集合内哪个顶点最近（即权值最小
    Tree T ;
    int start_num = -1;
    int count = 0;
    string start_vex;
a:    cout << "请输入起始顶点:";
    cin >> start_vex;
    for(int i = 0;i < ver_num;i++)
    {
        if(vertices[i].name == start_vex)
        {
            start_num = i;
        }
    }
    if(start_num == -1)
    {
        cout << "起点输入有误,请重新输入!";
        goto a;
    }
    for(int i = 0; i < ver_num;i++)
    {
        lowcost[i] = edge_value[start_num][i];
        nearvex[i] = start_num;
    }
    nearvex[start_num] = -1;//起点的最近顶点设置为-1表示已经在生成树顶点集合内
    for(int i = 0;i < ver_num;i++)
    {
        int mincost = INFINITY,v = start_num;
        for(int j = 0;j < ver_num;j++)
        {
            if(nearvex[j] != -1 && lowcost[j] < mincost)
            {
                v = j;
                mincost = lowcost[j];
            }
        }//forj
        if(v != start_num)
        {
            for(int k = 0; k < ver_num;k++)
            {
                if(v == vertices[k].num)
                {
                    T.tail = vertices[k].name;
                }
                else if(nearvex[v] == vertices[k].num)
                {
                    T.head = vertices[k].name;
                }
            }
            T.cost = mincost;
            MSTree.push(T);
            count++;
            nearvex[v] = -1;
            for(int j = 0;j < ver_num;j++)
            {
                if(nearvex[j] != -1 && edge_value[v][j] < lowcost[j])
                {
                    lowcost[j] = edge_value[v][j];
                    nearvex[j] = v;
                }
            }
        }
    }//for i
    if(count == ver_num-1)
    {
        Exist = true;
        cout << "生成Prim最小生成树!" << endl << endl;
    }
    else
    {
        Exist = false;
        cout << "不存在最小生成树!" << endl << endl;
    }
}

void MST::displayTree()
{
    if(Exist == false)
    {
        cout << "不存在最小生成树!" << endl << endl;
        return;
    }
    while(!MSTree.empty())
    {
        cout << MSTree.front().head << "-<" << MSTree.front().cost <<  ">->" << MSTree.front().tail << endl;
        MSTree.pop();
    }
}

int main()
{
    MST Tree;
    char order;
    cout << "**                     电网造价模拟系统                     **" << endl;
    cout << "============================================================" << endl;
    cout << "**                     A---创建电网的顶点                   **" << endl;
    cout << "**                     B---添加电网的的边                   **" << endl;
    cout << "**                     C---构造最小生成树                   **" << endl;
    cout << "**                     D---显示最小生成树                   **" << endl;
    cout << "**                     E---退出程序                        **" << endl;
    cout << "============================================================" << endl<<endl;
    cout << "请选择操作：";
    cin >> order;
    while (order!='E'){
        switch (order)
        {
        case 'A':
                Tree.createVertex();
                cout << endl;
            break;
        case 'B':
                Tree.addEdge();
                cout << endl;
            break;
        case 'C':
                Tree.createTree();
            break;
        case 'D':
                Tree.displayTree();
                cout << endl;
        default:
            break;
        }
        cout << "请选择操作：";
        cin >> order;
    }
    return 0;
}
