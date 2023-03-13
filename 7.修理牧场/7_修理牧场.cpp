//建立哈夫曼树 然后利用最小堆 选出权值最小的节点和次小的节点 然后合并重新插入最小堆 最后只剩下根节点 然后返回就是最后要的答案
//但是其实用最小堆就可以解决问题
#include<iostream>
int N;
using namespace std;
class MinHeap//最小堆类定义
{
public:
    MinHeap(int size = N);
    ~MinHeap()
    {
        delete []heap;
    }
    void Insert(int x);
    int RemoveMin();
    
    int * heap;
    int currentSize;
    void siftDown(int start,int m);
    void siftUp(int start);
};

MinHeap::MinHeap(int size)
{
    heap = new int[size];//创建存储空间
    currentSize = 0;//当前堆大小为0
}

void MinHeap::siftUp(int start)//向上比较函数
{
    int j = start,i=(j - 1)/2;
    int temp = heap[j];
    while(j > 0)
    {
        if(heap[i] <= temp)//父节点小于子节点 不交换
        {
            break;
        }
        else//父节点大于子节点 交换
        {
            heap[j] = heap[i];
            j = i;
            i = (i-1)/2;//循环终止条件是j<=0;比完一个父节点和子节点以后 继续往上比较j变成原来父节点在树中的次序,i变成新的父节点的次序
        }
    }
    heap[j] = temp;//将最下面的这个子节点 送到他该在的位置j
}

void MinHeap::Insert(int x)
{
    heap[currentSize] = x;
    siftUp(currentSize);
    currentSize++;
}

void MinHeap::siftDown(int start, int m)//最小堆下滑调整算法
{//从start到m 由上到下 如果子节点小于父节点 则子节点上浮 继续向下比较 将一个局部调整为最小堆
    int i = start, j = 2*i+1;//i为父节点在二叉树中的序号,j为子节点在二叉树中的序号
    int temp = heap[i];//将父节点的关键码记录
    while(j <= m)
    {
        if(j < m && heap[j] > heap[j+1])//让j指向两个子女中的较小者
        {
            j++;
        }
        if(heap[j] >= temp)//子节点小于父节点 子节点上浮
        {
            break;
        }
        else
        {
            heap[i] = heap[j];
            i = j;//继续向下比较
            j = 2*i+1;
        }
    }
    heap[i] = temp;//比完将temp放到他该在的地方
}

int MinHeap::RemoveMin()//取出最小堆中最小的数（即为heap[0]）,再讲最小堆重新排序
{
    if(!currentSize)//堆空
    {
        cout << "Heap EMPTY!" << endl;
        return false;
    }
    int x = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    siftDown(0,currentSize-1);
    return x;
}

int main()
{
    cin >> N;
    MinHeap heap;
    int result = 0,temp;
    for(int i = 0;i < N;i++)
    {
        cin >> temp;
        heap.Insert(temp);
    }
    if(N == 1)
    {
        cout << heap.RemoveMin();
    }
    else
    {
        for(int i = 0;i < N-1;i++)
        {
            int min1 = heap.RemoveMin();
            int min2 = heap.RemoveMin();
            heap.Insert(min1+min2);
            result = result + min1 + min2;
            //cout << i << ":" << min1 << "+" << min2 << "=" << result << endl;
        }
        cout << result;
    }
    return 0;
}
