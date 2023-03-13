//
//  main.cpp
//  Cpp test
//
//  Created by 董震宇 on 2019/10/8.
//  Copyright © 2019 董震宇. All rights reserved.
//



#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;


struct linklist
{
    int num;
    struct linklist * next;
};

typedef linklist* link;

link create()
{
    //带表头的节点 通过sub增加元素 所以sub一开始就要指向头结点  头结点不存任何东西   head赋值给q q指针指向head的位置
    link head = (link)malloc(sizeof(struct linklist));//创建头结点
    head->next = NULL;
    link sub = head;                                  //一个指向头结点的指针,用于遍历链表
    int num;
    while(cin >> num && num != -1)
    {
        link temp = (link)malloc(sizeof(struct linklist));//创建存储数据的结点
        temp->num =  num;
        temp->next = NULL;
        sub->next = temp;
        sub = temp;
    }
    return head;
}

void print(link a)
{
    a = a->next;
    if(a == NULL)
    {
        cout << "NULL" << endl;
        return;
    }
    else
    {
        while (a != NULL)
        {
            if(a->next != NULL)
            {
                cout << a->num << " ";
                a = a->next;
            }
            else
            {
                cout << a->num;
                a = a->next;
            }
        }
    }
}

link meet(link a,link b)
{
    a = a->next;
    b = b->next;
    link head = (link)malloc(sizeof(struct linklist));
    head ->next = NULL;
    link p1 = head;
    while(a != NULL && b!= NULL)
    {
        if(a->num == b->num)
        {
            link p2 = (link)malloc(sizeof(struct linklist));
            p2->num = a->num;
            p2->next = NULL;
            p1->next = p2;
            p1 = p2;
            a = a->next;
            b = b->next;
        }
        else if((a->num > b->num) || a == NULL)
        {
            b = b->next;
        }
        else if((b->num > a->num) || b == NULL)
        {
            a = a->next;
        }
    }
    return head;
}

int main()
{
    link a = create();
    link b = create();
    link c = meet(a,b);
    print(c);
    return 0;
}

//写在后面 链表确实掌握的不行 但写了就有进步  指针没学好是一大隐患 q=head  q指向head的位置 head是个指针 这是他们可以直接等的原因 从这个位置可以访问到数据 地址相同了 数据的入口相同了 就顺着访问到了
