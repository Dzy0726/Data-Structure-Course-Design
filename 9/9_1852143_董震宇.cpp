
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
using namespace std;

bool dzy = true;

struct Course
{
    int num;//下标
    string id;//课程序号
    string name;//课程名称
    int period;//周学时数
    int term;//开课学期
};

class Arrangement
{
public:
    int total;//课程总数
    int term_course[8];//每学期课程数
    Course * course;//课程数组 存储课程信息
    int **precourse;//先修关系
    queue<int> order;//队列暂时存储入度为0的顶点
    string * course_order;//存储上课的次序
    int * indegree;//入度数组
    string ** timetable;//初始化课程表用二维数组

public:
    Arrangement(){}
    ~Arrangement(){}
    void ReadInfo();//读入相关条件
    void getInDegree();//更新入度数组
    void getInDegree(int i);
    void TopoLogicalOrder();//拓扑排序
    int InsertCourse(string course,int period);//将课程插到课程表中
    void InsertCourse(string course,int period,int weekday);//将课程插到课程表中
    void TimeTable();//建立课程表
};


void Arrangement::ReadInfo()
{
    ifstream info("/Users/dzy/desktop/course.txt");
    if(!info)
    {
        cerr << "文件打开失败！" << endl;
        dzy = false;
        return;
    }
    info >> total;
    
    int sum = 0;
    for(int i = 0;i < 8;i++)
    {
        info >> term_course[i];
        sum = sum + term_course[i];
    }
    
    if(sum != total)
    {
        cerr << "每学期课程数之和与总课程数不相等！" << endl;
        dzy = false;
        return;
    }
    
    course = new Course[total];
    for(int i = 0;i < total;i++)
    {
        info >> course[i].id >> course[i].name >> course[i].period >> course[i].term;
        course[i].num = i;
    }
    
    //初始化邻接矩阵(先修关系二维数组)
    //-1表示没有先修关系 precourse[0][1]=1表示0的先修是1
    precourse = new int*[total];
    for(int i = 0;i < total;i++)
    {
        precourse[i] = new int[total];
    }
    for(int i = 0;i < total;i++)
    {
        for(int j = 0;j < total;j++)
        {
            precourse[i][j] = -1;
        }
    }
    
    string a,b;
    int m = -1 ,n = -1;
    info >> a;
    while(a != "-1")
    {
        info >> b;
        for(int i = 0;i < total;i++)
        {
            if(course[i].id == a)
            {
                m = course[i].num;
            }
            else if(course[i].id == b)
            {
                n = course[i].num;
            }
        }
        if(m != -1 && n != -1)
        {
            precourse[m][n] = 1;
        }
        info >> a;
    }
    info.close();
}

void Arrangement::getInDegree()
{
    indegree = new int[total];
    for(int i = 0; i < total;i++)
    {
        indegree[i] = 0;
        for(int j = 0;j < total;j++)
        {
            if(precourse[i][j] == 1)
            {
                indegree[i]++;
            }
        }
    }
}

void Arrangement::getInDegree(int a)
{
    //以a为先修课程的课的入度-1 即先修关系为-1 不存在先修因为a已经学了
    for(int i = 0;i < total;i++)
    {
        if(precourse[i][a] == 1)
        {
            precourse[i][a] = -1;
        }
    }
    getInDegree();//重新获得入度数组
}

void Arrangement::TopoLogicalOrder()
{
    int count = 0,k = 0;//用于记录已经输出顶点的个数 k为循环变量
    course_order = new string[total];//初始化顺序数组
    for(int i  = 0;i < total; i++)
    {
        if(indegree[i] == 0)
        {
            order.push(i);
            getInDegree(i);
            break;//找到一个就进入下面的循环
        }
    }
    while(!order.empty() && count < total)//队列不空且输出顶点个数小于总数
    {
        int j =  order.front();
        order.pop();
        for(int i = 0;i < total;i++)
        {
            if(course[i].num == j)
            {
                //cout << course[i].id << "    ";
                course_order[k] = course[i].name;
                course[i].num  = k-1000;//删去这个顶点
                count++;
                k++;
            }
        }
        for(int i = 0;i < total;i++)
        {
            if(indegree[i] == 0 && course[i].num >= 0)
            {
                order.push(i);
                getInDegree(i);//删去与i顶点相关的边
                break;
            }
        }
    }
}

int Arrangement::InsertCourse(string course, int period)
{
    if(period == 3)
    {
        for(int i = 0;i < 5;i++)
        {
            for(int j = 2;j < 10;j = j+5)
            {
                if(timetable[j][i] == "NULL")
                {
                    timetable[j][i] = course;
                    timetable[j+1][i] = course;
                    timetable[j+2][i] = course;
                    return i;//返回星期数
                }
            }
        }
    }
    else if(period == 2)
    {
        for(int i = 0;i < 5;i++)
        {
            for(int j = 0;j < 10;j = j+5)
            {
                if(timetable[j][i] == "NULL")
                {
                    timetable[j][i] = course;
                    timetable[j+1][i] = course;
                    return i;//返回星期数
                }
            }
        }
    }
    else if (period == 1)
    {
        for(int i = 0;i < 5;i++)
        {
            for(int j = 0;j < 10;j = j+5)
            {
                if(timetable[j][i] == "NULL")
                {
                    timetable[j][i] = course;
                    return i;//返回星期数
                }
            }
        }
    }
    return -1;
}

void Arrangement::InsertCourse(string course, int period, int weekday)
{
    if(period == 3)
    {
        for(int j = 2;j < 10;j = j+5)
        {
            if(timetable[j][weekday]== "NULL")
            {
                timetable[j][weekday] = course;
                timetable[j+1][weekday] = course;
                timetable[j+2][weekday] = course;
                break;
            }
        }
    }
    else if(period == 2)
    {
        for(int j = 0;j < 10;j = j+5)
        {
            if(timetable[j][weekday] == "NULL")
            {
                timetable[j][weekday] = course;
                timetable[j+1][weekday] = course;
                break;
            }
        }
    }
    else if (period == 1)
    {
        for(int j = 0;j < 10;j = j+5)
        {
            if(timetable[j][weekday] == "NULL")
            {
                timetable[j][weekday] = course;
                break;
            }
        }
    }
}

void Arrangement::TimeTable()
{
    ofstream table("/Users/dzy/Desktop/timetable.txt");
    for(int i = 0;i < 8;i++)
    {
        string * this_term_course = new string[term_course[i]];//存储当前学期需要学习的课程
        int * xueshi = new int[term_course[i]];//当前学期课程对应的学时
        int count1 = 0,count2 = 0;//本学期课程计数
        timetable = new string*[10];
        for(int j = 0;j < 10;j++)
        {
            timetable[j] = new string[5];
        }
        for(int j = 0;j < 10;j++)
        {
            for(int k = 0;k < 5;k++)
            {
                timetable[j][k] = "NULL";
            }
        }
        //---------把课程分到8个学期--------//
        for(int j = 0;j < total;j++)//指定在本学期开课的课程加入本学期的课程数组
        {
            if(course[j].term == i+1 && count2 < term_course[i])
            {
                this_term_course[count1] = course[j].name;
                course_order[course[j].num+1000] = "NULL";//上过的课做个标记
                count1++;
                count2++;
            }
        }
        for(int j = 0;j < total && count1 < term_course[i];j++)
        {
            if(course_order[j] != "NULL")
            {
                int now_term = -1;
                for(int k = 0; k < total;k++)
                {
                    if(course[k].name == course_order[j])
                    {
                        now_term = course[k].term;
                    }
                }
                if( now_term == 0)
                {
                    this_term_course[count1++] = course_order[j];
                    course_order[j] = "NULL";
                }
            }
        }
        table << "第"<< i+1 << "学期"<< endl;
        //---------把课程分到8个学期--------//
        //---------每个学期按学时分配--------//
        for(int j = 0; j < term_course[i];j++)
        {
            for(int k = 0; k < total;k++)
            {
                if(course[k].name == this_term_course[j])
                {
                    xueshi[j] = course[k].period;
                }
            }
        }
        for(int j = 0; j < term_course[i];j++)
        {
            int weekday = 0;
            if(xueshi[j] ==  3)
            {
                weekday = InsertCourse(this_term_course[j],3);
                if(weekday == -1)
                {
                    weekday = InsertCourse(this_term_course[j],2);
                    weekday = weekday+2 < 5? weekday+2:weekday;
                    InsertCourse(this_term_course[j], 1, weekday);
                }
            }
            else if (xueshi[j] == 4)
            {
                weekday = InsertCourse(this_term_course[j],2);
                weekday = weekday+2 < 5? weekday+2:weekday;
                InsertCourse(this_term_course[j], 2, weekday);
            }
            else if (xueshi[j] == 5)
            {
                weekday = InsertCourse(this_term_course[j],3);
                weekday = weekday+2 < 5? weekday+2:weekday;
                InsertCourse(this_term_course[j], 2, weekday);
            }
            else
            {
                weekday = InsertCourse(this_term_course[j],3);
                weekday = weekday+2 < 5? weekday+2:weekday;
                InsertCourse(this_term_course[j], 3, weekday);
            }
        }
        table << "\t\t" << "星期一"  << "\t\t\t"<< "星期二"<< "\t\t\t"<< "星期三"<< "\t\t\t"<< "星期四"<<"\t\t\t"<< "星期五" << endl;
        for(int b = 0;b < 10;b++)
        {
            if(b < 9)
            {
                table << "第 " << b+1 << " 节  ";
            }
            else
            {
                table << "第" << b+1 << " 节  ";
            }
            for(int j = 0; j < 5;j++)
            {
                if(timetable[b][j] != "NULL")
                {
                    table << left << setw(30)<<timetable[b][j];
                }
                else
                {
                    table << left << setw(25) << " ";
                }
            }
            table << endl;
        }
        delete[] timetable;
    }//for i < 8
    table.close();
}


int main()
{
    Arrangement a;
    a.ReadInfo();
    if(dzy == false)
    {
        return 0;
    }
    a.getInDegree();
    a.TopoLogicalOrder();
    a.TimeTable();
    cout << "success!" << endl;
}
