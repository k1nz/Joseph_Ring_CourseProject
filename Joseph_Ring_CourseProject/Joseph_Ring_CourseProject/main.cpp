/*                                              *
*@file     Joseph_Ring.cpp                      *
*@brief    基于约瑟夫环的数字游戏数据结构设计         *
*@Details                                       *
*                                               *
*@author   qiuzirong                            *
*@email    kinz.qiu@foxmail.com                 *
*@version  1.0.0.1                              *
*@date     2020/6/26                            *
*@license  GNU General Public License(GPL)      *
*/


#include <iostream>  
#include <stdlib.h>  
#include <time.h>  
using namespace std;
#define MAXPLAYER 100   //最大玩家数设置，用于定义存放密码的数组长度  
#define MIN 1  
#define MAX 30 // 设置随机数的最大和最小值  

typedef int NameType;
typedef int PwdType;

typedef struct node
{
    NameType name;
    PwdType pwd;
    struct node* next;
}node, * Linklist;

// 创建并初始化一个带头节点的单链表  
Linklist init_ring(int n)  
{
    Linklist head, p, tail; // 创建头指针head, 当前指针p，尾指针tail  
    // 由于本游戏游玩人数大于等于2人，无需考虑只有一个节点的情况  
    head = new node;    // 创建头节点  
    tail = new node;    // 创建尾结点  
    head->next = tail;   // 将第一个节点接到头指针的next  
    tail->next = head->next;  // 尾指针指向第一个节点  
    p = head->next;      //当前节点指向第一个节点  

    for (int i = 1; i < n; i++)  //创建单链表  
    {
        tail->next = new node;   // 在尾节点插入新节点  
        tail = tail->next;   // 将尾指针指向尾结点  
        tail->next = head->next; //尾结点的后继设为首结点  
    }

    for (int i = 1; i <= n; i++)  //初始化单链表  
    {
        p->name = i; // 玩家编号  
        p->pwd = MIN + rand() % (MAX + MIN - 1);   // 随机获取密码  
        p = p->next; // 将当前指针指向下一节点  
    }
    cout << "  初始化完成" << endl << endl;
    return head; // 返回头指针  
}

// 删除目标节点，并返回当前节点的密码  
PwdType del_node(Linklist& head, Linklist& pre, Linklist& target, NameType& TempName, int count) 
{
    PwdType temp = target->pwd;  // 将出队的节点密码保存  
    TempName = target->name; // 将出队的节点名称保存  

    if (head->next == target)    // 如果要出队的节点为头结点的后继结点，则将头节点的next域设置为当前节点的next域  
        head->next = target->next;
    pre->next = target->next;
    free(target);   // 释放当前节点  
    target = pre->next;  // 将当前指针指向pre->next  

    cout << "第" << count << "出列的序号为-> " << TempName << "，其密码为 " << temp << endl;

    return temp;    // 返回出列的密码  
}

NameType Operate_Ring(Linklist head, NameType NameArr[], PwdType n)
{
    NameType last, TempName;
    PwdType initPwd = MIN + rand() % (MAX + MIN - 1); // 设置一个随机初始密码  
    Linklist pre, target;  // 设置指向当前节点指针target，以及指向当前节点前驱节点pre  
    int ele = 0, count = 0;
    pre = head;
    target = head->next;
    cout << "初始随机密码为：" << initPwd << endl;

    while (head->next)   // 当首结点不为空时反复执行  
    {
        int now = 1;    // 设置当前计数次数  
        while (now != initPwd)    // 当计数次数不等于默认密码时反复执行  
        {
            target = target->next;   // 将目标指针指向后继  
            pre = pre->next; // 目标前驱指向后继  
            now++;  // 计数+1  
        }
        initPwd = del_node(head, pre, target, TempName, ++count);   // 删除出列节点，并返回其密码  
        NameArr[ele++] = TempName;   // 将出队名存入数组  
        if (target->next == target)  //若链表中只剩下一个节点，则直接删除该节点并返回密码  
        {
            del_node(head, pre, target, last, ++count); // 删除首结点  
            head->next = NULL;   // 首结点置空  
            TempName = last;
            NameArr[ele] = TempName;
        }
    }
    return last;  // 返回最后胜利者名字(编号)  
}

void menu()
{
    cout << "************************** 约瑟夫环 *************************" << endl;
    cout << "*           [1] 约瑟夫环问题概述                            *" << endl;
    cout << "*           [2] 求解约瑟夫环                                *" << endl;
    cout << "*           [0] 退出程序                                    *" << endl;
    cout << "*************************************************************" << endl;
}

void description()
{
    cout << "约瑟夫环问题：" << endl;
    cout << "    有n个人一起玩游戏，编号分别为1，2 … n，并按顺时针方向围坐一圈，每" << endl;
    cout << "人持有一个密码（正整数）。一开始任选一个正整数作为报数的上限值m，从第" << endl;
    cout << "一个人开始按顺时针方向自1开始顺序报数，报到m时停止报数，报m的人出" << endl;
    cout << "列，将他的密码作为新的m值，从他的顺时针方向上的下一个开始重新从1报" << endl;
    cout << "数，如此下去，直至所有人全部出列为止，最后一个出列的人为最终胜利者。设" << endl;
    cout << "计一个程序求出出列顺序，得出游戏最终胜利者的编号。" << endl << endl << endl;
}

void JosephRing()
{
    Linklist h;
    srand((unsigned)time(NULL)); // 初始化随机数发生器  
    int n;
    cout << "***************约瑟夫环***************" << endl << endl;
    while (true)
    {
        cout << "请输入游戏人数(2-" << MAXPLAYER << "人)：";
        cin >> n;  // n >= 2  
        if (n >= 2 && n <= MAXPLAYER)
            break;
        else
            cout << "游戏人数范围应在2-100人！请重新输入" << endl;
    }

    NameType player[MAXPLAYER]; // 创建一个数组存放出列的玩家  
    cout << "正在初始化中>>>";
    h = init_ring(n);
    
    int winner = Operate_Ring(h, player, n);
    cout << endl << "出列序列为：";
    for (int i = 0; i < n; i++)
    {
        cout << " " << player[i];
    }
    cout << endl << "最终胜利者：" << winner << endl;
    cout << "求解完成" << endl << endl;
}

int main()
{
    int n;
    while (true)
    {
        menu();
        cout << endl << "请选择要执行的操作，输入序号回车确认：" << endl;
        cin >> n;
        system("cls");
        switch (n)
        {
        case 1:
            description();
            break;

        case 2:
            JosephRing();
            break;

        case 0:
            exit(0);

        default:
            system("cls");
            cout << endl << "您选择有误请重新选择" << endl << endl;
            break;
        }
    }
    return 0;
}

