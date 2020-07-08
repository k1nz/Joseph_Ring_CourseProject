/*                                              *
*@file     Joseph_Ring.cpp                      *
*@brief    ����Լɪ�򻷵�������Ϸ���ݽṹ���         *
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
#define MAXPLAYER 100   //�����������ã����ڶ�������������鳤��  
#define MIN 1  
#define MAX 30 // �����������������Сֵ  

typedef int NameType;
typedef int PwdType;

typedef struct node
{
    NameType name;
    PwdType pwd;
    struct node* next;
}node, * Linklist;

// ��������ʼ��һ����ͷ�ڵ�ĵ�����  
Linklist init_ring(int n)  
{
    Linklist head, p, tail; // ����ͷָ��head, ��ǰָ��p��βָ��tail  
    // ���ڱ���Ϸ�����������ڵ���2�ˣ����迼��ֻ��һ���ڵ�����  
    head = new node;    // ����ͷ�ڵ�  
    tail = new node;    // ����β���  
    head->next = tail;   // ����һ���ڵ�ӵ�ͷָ���next  
    tail->next = head->next;  // βָ��ָ���һ���ڵ�  
    p = head->next;      //��ǰ�ڵ�ָ���һ���ڵ�  

    for (int i = 1; i < n; i++)  //����������  
    {
        tail->next = new node;   // ��β�ڵ�����½ڵ�  
        tail = tail->next;   // ��βָ��ָ��β���  
        tail->next = head->next; //β���ĺ����Ϊ�׽��  
    }

    for (int i = 1; i <= n; i++)  //��ʼ��������  
    {
        p->name = i; // ��ұ��  
        p->pwd = MIN + rand() % (MAX + MIN - 1);   // �����ȡ����  
        p = p->next; // ����ǰָ��ָ����һ�ڵ�  
    }
    cout << "  ��ʼ�����" << endl << endl;
    return head; // ����ͷָ��  
}

// ɾ��Ŀ��ڵ㣬�����ص�ǰ�ڵ������  
PwdType del_node(Linklist& head, Linklist& pre, Linklist& target, NameType& TempName, int count) 
{
    PwdType temp = target->pwd;  // �����ӵĽڵ����뱣��  
    TempName = target->name; // �����ӵĽڵ����Ʊ���  

    if (head->next == target)    // ���Ҫ���ӵĽڵ�Ϊͷ���ĺ�̽�㣬��ͷ�ڵ��next������Ϊ��ǰ�ڵ��next��  
        head->next = target->next;
    pre->next = target->next;
    free(target);   // �ͷŵ�ǰ�ڵ�  
    target = pre->next;  // ����ǰָ��ָ��pre->next  

    cout << "��" << count << "���е����Ϊ-> " << TempName << "��������Ϊ " << temp << endl;

    return temp;    // ���س��е�����  
}

NameType Operate_Ring(Linklist head, NameType NameArr[], PwdType n)
{
    NameType last, TempName;
    PwdType initPwd = MIN + rand() % (MAX + MIN - 1); // ����һ�������ʼ����  
    Linklist pre, target;  // ����ָ��ǰ�ڵ�ָ��target���Լ�ָ��ǰ�ڵ�ǰ���ڵ�pre  
    int ele = 0, count = 0;
    pre = head;
    target = head->next;
    cout << "��ʼ�������Ϊ��" << initPwd << endl;

    while (head->next)   // ���׽�㲻Ϊ��ʱ����ִ��  
    {
        int now = 1;    // ���õ�ǰ��������  
        while (now != initPwd)    // ����������������Ĭ������ʱ����ִ��  
        {
            target = target->next;   // ��Ŀ��ָ��ָ����  
            pre = pre->next; // Ŀ��ǰ��ָ����  
            now++;  // ����+1  
        }
        initPwd = del_node(head, pre, target, TempName, ++count);   // ɾ�����нڵ㣬������������  
        NameArr[ele++] = TempName;   // ����������������  
        if (target->next == target)  //��������ֻʣ��һ���ڵ㣬��ֱ��ɾ���ýڵ㲢��������  
        {
            del_node(head, pre, target, last, ++count); // ɾ���׽��  
            head->next = NULL;   // �׽���ÿ�  
            TempName = last;
            NameArr[ele] = TempName;
        }
    }
    return last;  // �������ʤ��������(���)  
}

void menu()
{
    cout << "************************** Լɪ�� *************************" << endl;
    cout << "*           [1] Լɪ���������                            *" << endl;
    cout << "*           [2] ���Լɪ��                                *" << endl;
    cout << "*           [0] �˳�����                                    *" << endl;
    cout << "*************************************************************" << endl;
}

void description()
{
    cout << "Լɪ�����⣺" << endl;
    cout << "    ��n����һ������Ϸ����ŷֱ�Ϊ1��2 �� n������˳ʱ�뷽��Χ��һȦ��ÿ" << endl;
    cout << "�˳���һ�����루����������һ��ʼ��ѡһ����������Ϊ����������ֵm���ӵ�" << endl;
    cout << "һ���˿�ʼ��˳ʱ�뷽����1��ʼ˳����������mʱֹͣ��������m���˳�" << endl;
    cout << "�У�������������Ϊ�µ�mֵ��������˳ʱ�뷽���ϵ���һ����ʼ���´�1��" << endl;
    cout << "���������ȥ��ֱ��������ȫ������Ϊֹ�����һ�����е���Ϊ����ʤ���ߡ���" << endl;
    cout << "��һ�������������˳�򣬵ó���Ϸ����ʤ���ߵı�š�" << endl << endl << endl;
}

void JosephRing()
{
    Linklist h;
    srand((unsigned)time(NULL)); // ��ʼ�������������  
    int n;
    cout << "***************Լɪ��***************" << endl << endl;
    while (true)
    {
        cout << "��������Ϸ����(2-" << MAXPLAYER << "��)��";
        cin >> n;  // n >= 2  
        if (n >= 2 && n <= MAXPLAYER)
            break;
        else
            cout << "��Ϸ������ΧӦ��2-100�ˣ�����������" << endl;
    }

    NameType player[MAXPLAYER]; // ����һ�������ų��е����  
    cout << "���ڳ�ʼ����>>>";
    h = init_ring(n);
    
    int winner = Operate_Ring(h, player, n);
    cout << endl << "��������Ϊ��";
    for (int i = 0; i < n; i++)
    {
        cout << " " << player[i];
    }
    cout << endl << "����ʤ���ߣ�" << winner << endl;
    cout << "������" << endl << endl;
}

int main()
{
    int n;
    while (true)
    {
        menu();
        cout << endl << "��ѡ��Ҫִ�еĲ�����������Żس�ȷ�ϣ�" << endl;
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
            cout << endl << "��ѡ������������ѡ��" << endl << endl;
            break;
        }
    }
    return 0;
}

