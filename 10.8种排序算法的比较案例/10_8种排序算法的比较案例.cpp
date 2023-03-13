#include <iostream>
#include <cstring>
#include <ctime>
#include <cmath>

using namespace std;
int N = 0;
int Count = 0;

void Print(int a[])
{
    for(int i = 0;i < N;i++)
    {
        cout << a[i] << "\t";
    }
}
/*--------------冒泡排序---------------*/
void BubbleSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    int count = 0;
    clock_t stime,etime;
    stime = clock();
    int flag = 1;//是否发生交换标志，默认无序即发生了交换
    
    for (int i = 0; (i < N) && flag; i++)
    {
        flag = 0;
        for (int j = N - 2; j >= i; j--)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                flag = 1;
                count++;
            }
        }
    }
    etime = clock();
    
    cout << "冒泡排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "冒泡排序交换次数：      " << count << endl;
    //Print(a);
    delete[] a;
}
/*--------------选择排序---------------*/
void SelectionSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    int count = 0;
    clock_t stime,etime;
    stime = clock();
    
    int i = 0, j = 0, min = 0;
    for (i = 0; i < N; i++)
    {
        min = i;
        for (j = i + 1; j < N; j++)
        {
            if (a[min] > a[j])
            {
                min = j;
            }
        }
        if (i != min)
        {
            swap(a[min], a[i]);
            count++;
        }
    }
    
    etime = clock();
    
    cout << "选择排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "选择排序交换次数：      " << count << endl;
    //Print(a);
    delete[] a;
}
/*--------------直接插入排序---------------*/
void InsertionSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    int count = 0;
    clock_t stime,etime;
    stime = clock();
    
    int tmp = 0;
    for (int i = 1; i < N; i++)
    {
        int k = i;//需要插入的位置
        tmp = a[i];
        for (int j = i - 1; (j >= 0) && (a[j] > tmp); j--)
        {
            count++;
            a[j + 1] = a[j];
            k = j;
        }
        a[k] = tmp;
    }
    
    etime = clock();
    
    cout << "直接插入排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "直接插入排序交换次数：      " << count << endl;
    //Print(a);
    delete[] a;
}
/*--------------希尔排序---------------*/
void ShellSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    int count = 0;
    clock_t stime,etime;
    stime = clock();
    
    int tmp = 0;
    int gap = N;
    do
    {
        gap = gap / 3 + 1;
        for (int i = gap; i < N; i += gap)
        {
            int k = i;//需要插入的位置
            tmp = a[i];
            for (int j = i - gap; (j >= 0) && (a[j] > tmp); j -= gap)
            {
                a[j + gap] = a[j];
                k = j;
                count++;
            }
            a[k] = tmp;
        }
 
    } while (gap > 1);
    
    etime = clock();
    
    cout << "希尔排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "希尔排序交换次数：      " << count << endl;
    //Print(a);
    delete[] a;
}
/*--------------快速排序---------------*/
void QuickSort_help(int a[],int left,int right)
{
    if (left < right)
    {
        int i = left, j = right, x = a[left];
        while (i < j && a[j] >= x)
            j--;//从右到左找到第一个小于X的数
        if (i < j)
        {
            a[i++] = a[j];
            Count++;
        }
        while (i < j && a[i] <= x)
            i++;//从左到右找到第一个大于X的数
        if (i < j)
        {
            Count++;
            a[j--] = a[i];
        }
        a[i] = x;//x放在中间
        QuickSort_help(a, left, i-1);
        QuickSort_help(a, i+1, right);
    }
}
void QuickSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    clock_t stime,etime;
    stime = clock();
    
    QuickSort_help(a,0, N-1);
    
    etime = clock();
       
   cout << "快速排序所用时间：      " << etime - stime << "ms" << endl;
   cout << "快速排序交换次数：      " << Count << endl;
    //Print(a);
    delete[] a;
    Count = 0;
}
/*--------------堆排序---------------*/
void adjust(int a[],int len,int index)
{
    int left = 2 * index + 1; // index的左子节点
    int right = 2 * index + 2;// index的右子节点
 
    int maxIdx = index;
    if (left<len && a[left] > a[maxIdx])
        maxIdx = left;
    if (right<len && a[right] > a[maxIdx])
        maxIdx = right;
    if (maxIdx != index)
    {
        swap(a[maxIdx], a[index]);
        Count++;
        adjust(a, len, maxIdx);
    }
 
}
void HeapSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    clock_t stime,etime;
    stime = clock();
    
    // 构建大根堆（从最后一个非叶子节点向上）
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        adjust(a, N, i);
    }
 
    // 调整大根堆
    for (int i = N - 1; i >= 1; i--)
    {
        swap(a[0], a[i]);           // 将当前最大的放置到数组末尾
        Count++;
        adjust(a, i, 0);              // 将未完成排序的部分继续进行堆排序
    }
    
    etime = clock();
        
    cout << "堆排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "堆排序交换次数：      " << Count << endl;
   // Print(a);
    delete[] a;
    Count = 0;
}
/*--------------归并排序---------------*/
//合并有序数组
void merge_help2(int arr[], int temp[], int start, int mid, int end){
    int i = start, j = mid + 1, k = start;
    while (i != mid + 1 && j != end + 1){
        if (arr[i] > arr[j]){
            temp[k++] = arr[i++];
            Count++;
        }
        else{
            temp[k++] = arr[j++];
            Count++;
        }
    }
    while (i != mid + 1)
        temp[k++] = arr[i++];
    while (j != end + 1)
        temp[k++] = arr[j++];
    for (i = start; i <= end; i++)
        arr[i] = temp[i];
}

void merge_help1(int arr[], int temp[], int start, int end){
    int mid;
    if (start < end){
        mid = (start + end) / 2;
        merge_help1(arr, temp, start, mid);
        merge_help1(arr, temp, mid + 1, end);
        merge_help2(arr, temp, start, mid, end);
    }
}
void MergeSort(int arr[])
{
    int * a = new int[N];
    memcpy(a, arr, N*sizeof(int));
    
    clock_t stime,etime;
    stime = clock();
    
    merge_help1(a, arr, 0, N - 1);
    
    etime = clock();
        
    cout << "归并排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "归并排序交换次数：      " << Count << endl;
    //Print(a);
    delete[] a;
    Count = 0;
}
/*--------------基数排序---------------*/
void RadixSort(int arr[]){
    int getPlaces(int num);
    int getMax(int arr[], int n);
    void radix_help(int arr[], int n, int place);

    int *test, max, maxPlaces;
    clock_t stime,etime;

    test = new int[N];
    memcpy(test, arr, sizeof(int) * N);
    
    stime = clock();
    max = getMax(test, N);
    maxPlaces = getPlaces(max);

    for (int i = 1; i <= maxPlaces; i++)
        radix_help(test, N, i);

    etime = clock();
        
    cout << "基数排序所用时间：      " << etime - stime << "ms" << endl;
    cout << "基数排序交换次数：      " << Count << endl;
    delete[] test;
    //print(test);
    Count = 0;
}

int getPlaces(int num){
    int count = 1;
    int temp = num / 10;
    while (temp != 0){
        count++;
        temp /= 10;
    }
    return count;
}

int getMax(int arr[], int n){
    int max = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void radix_help(int arr[], int n, int place){
    int buckets[10][100] = {NULL};
    int temp = (int)pow(10, place - 1);
    for (int i = 0; i < n; i++){
        int row = (arr[i] / temp) % 10;
        for (int j = 0; j < 100; j++){
            if (buckets[row][j] == NULL){
                Count++;
                buckets[row][j] = arr[i];
                break;
            }
        }
    }
    int k = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 20; j++){
            if (buckets[i][j] != NULL){
                arr[k] = buckets[i][j];
                buckets[i][j] = NULL;
                k++;
            }
        }
    }
}
int main()
{
        cout << "**                               排序算法比较                               **" << endl;
        cout << "==============================================================================" << endl;
        cout << "**                              1 --- 冒泡排序                              **" << endl;
        cout << "**                              2 --- 选择排序                              **" << endl;
        cout << "**                              3 --- 直接插入排序                          **" << endl;
        cout << "**                              4 --- 希尔排序                              **" << endl;
        cout << "**                              5 --- 快速排序                              **" << endl;
        cout << "**                              6 --- 堆排序                                **" << endl;
        cout << "**                              7 --- 归并排序                              **" << endl;
        cout << "**                              8 --- 基数排序                              **" << endl;
        cout << "**                              9 --- 退出程序                              **" << endl;
        cout << "==============================================================================" << endl;

        int order;
        srand((int)time(NULL));
        cout << "请输入要产生的随机数的个数：";
        cin >> N;
        int * array = new int[N];
        for (int i = 0; i < N; i++)
        {
            array[i] = rand() % N;
        }
        //Print(array);
        cout << endl << "请选择排序算法:        ";
        cin >> order;
        while (order != 9){
            switch (order){
            case 1:
                BubbleSort(array);
                break;
            case 2:
                SelectionSort(array);
                break;
            case 3:
                InsertionSort(array);
                break;
            case 4:
                ShellSort(array);
                break;
            case 5:
                QuickSort(array);
                break;
            case 6:
                HeapSort(array);
                break;
            case 7:
                MergeSort(array);
                break;
            case 8:
                RadixSort(array);
                break;
            default:
                cout << "输入有误!" << endl;
            }
            cout << endl << "请选择排序算法:        ";
            cin >> order;
        }
        return 0;
}
