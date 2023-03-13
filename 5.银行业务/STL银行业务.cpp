#include <iostream>
#include <queue>

using namespace std;

int main()
{
    queue<int> jishu;
    queue<int> oushu;
    int n,m;
    cin >> n;
    while (n--)
    {
        cin >> m;
        if(m % 2 == 0)
        {
            oushu.push(m);
        }
        else
        {
            jishu.push(m);
        }
    }
    while(jishu.size() && oushu.size())
    {
        cout << jishu.front() << " ";
        jishu.pop();
        cout << jishu.front() << " ";
        jishu.pop();
        cout << oushu.front() << " ";
        oushu.pop();
    }
    while(jishu.size() > 0)
    {
        if(jishu.size() != 1)
        {
            cout << jishu.front() << " ";
            jishu.pop();
        }
        else
        {
            cout << jishu.front();
            jishu.pop();
        }
    }
    while(oushu.size() > 0)
    {
        if(oushu.size() != 1)
        {
            cout << oushu.front() << " ";
            oushu.pop();
        }
        else
        {
            cout << oushu.front();
            oushu.pop();
        }
    }
    return 0;
}
