#include <iostream>
#include <string>

#define N 7
#define M 7     //定义迷宫大小

using namespace std;

//测试迷宫
char maze[N][M]=
    {
        {'#','#','#','#','#','#','#'},
        {'#','0','#','0','0','0','#'},
        {'#','0','#','0','#','#','#'},
        {'#','0','0','0','#','#','#'},
        {'#','#','#','0','0','0','#'},
        {'#','0','#','0','#','0','#'},
        {'#','#','#','#','#','#','#'},
    };

int mark[N][M];//用来记录某点是否走过

int startX,startY;//起点坐标
int endX,endY;//终点坐标

int sum = 2;//记录路径访问顺序

struct Node
{
    int X;
    int Y;
    Node* next;
};
Node *p = new Node;//创建带头结点的单链表以便于顺序输出通路坐标
Node *temp = NULL;

bool FindPath(int i,int j)
{
    if(i == endX && j == endY)
    {
        return true;
    }
    else
    {
        if(maze[i+1][j] == '0' && mark[i+1][j] == 0)//分别向上下左右四个方向（可以用for循环+方向数组代替）
        {
            mark[i+1][j] = 1;
            if(FindPath(i+1, j))
            {
                //cout << "(" << i+1 << "," << j << ")->";//这个是反向路径
                temp = new Node;
                temp->X = i+1;
                temp->Y = j;
                temp->next = p->next;
                p->next = temp;//用单链表头插法记录路径
                mark[i+1][j] =sum;
                sum++;
                return true;
            }
        }
        if(maze[i][j+1] == '0' && mark[i][j+1] == 0)
        {
            mark[i][j+1] = 1;
            if(FindPath(i, j+1))
            {
                temp = new Node;
                //cout << "(" << i << "," << j+1 << ")->";
                temp->X = i;
                temp->Y = j+1;
                temp->next = p->next;
                p->next = temp;
                mark[i][j+1] = sum;
                sum++;
                return true;
            }
        }
        if(maze[i-1][j] == '0' && mark[i-1][j] == 0)
        {
            mark[i-1][j] = 1;
            if(FindPath(i-1, j))
            {
                temp = new Node;
                //cout << "(" << i-1 << "," << j << ")->";
                temp->X = i-1;
                temp->Y = j;
                temp->next = p->next;
                p->next = temp;
                mark[i-1][j] = sum;
                sum++;
                return true;
            }
        }

        if(maze[i][j-1] == '0' && mark[i][j-1] == 0)
        {
            mark[i][j-1] = 1;
            if(FindPath(i, j-1))
            {
                temp = new Node;
                //cout << "(" << i << "," << j-1 << ")->";
                temp->X = i;
                temp->Y = j-1;
                temp->next = p->next;
                p->next = temp;
                mark[i][j-1] = sum;
                sum++;
                return true;
            }
        }

    }
    return false;
}


int main()
{
    //打印迷宫地图
    cout << "迷宫地图:" <<endl;
    cout << "\t";
    for(int i = 0;i < M;i++)
    {
        cout << i << "列" << "\t";
    }
    cout << endl;
    for(int i = 0;i < N;i++)
    {
        cout << i << "行" << "\t";
        for(int j = 0;j < M;j++)
        {
            cout << maze[i][j] << "\t";
        }
        cout << endl;
    }
    
    cout << "请输入迷宫入口:(入口坐标,用空格隔开)" << endl;
    cin >> startX >> startY;
    cout << "请输入迷宫出口:(出口坐标,用空格隔开)" << endl;
    cin >> endX >> endY;
    
    memset(mark,0,sizeof(mark));//标记走过的点
    mark[startX][startY] = 1;
    
    p->next = NULL;
    temp = p->next;
    if(FindPath(startX,startY))
    {
        cout << "迷宫路径:" << endl;
        cout << "(" << startX << "," << startY << ")->" ;
        p = p->next;
        while (p != NULL)
        {
            cout << "(" << p->X << "," << p->Y << ")";
            if(p->next != nullptr)
            {
                cout << "->";
            }
            else
            {
                cout << endl;
            }
            p = p->next;
        }
    }
    else
    {
        cout << "没有找到从入口到出口的路径!" << endl;
    }
    delete temp;
    return 0;
}
