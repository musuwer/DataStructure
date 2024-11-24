#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h>
#include <malloc.h> // 包含动态内存分配的头文件

typedef int DataType;// 定义数据类型为整型

// 定义链表节点结构体
typedef struct Node {
    DataType xishu; // 系数
    DataType index; // 指数
    struct Node* next; // 指向下一个节点的指针
} SLNode, * LinkList; 

void ListInitiate(LinkList* head);// 初始化链表，创建一个头节点
int ListLength(SLNode* head);// 获取链表的长度
int ListInsert(SLNode* head, int i, DataType a, DataType b);// 在链表指定位置插入新节点
int ListGet(SLNode* head, int i, DataType* x, DataType* y);// 获取链表中指定位置的节点的系数和指数
int ListDelete(SLNode* head, int i, DataType* x);// 删除链表中指定位置的节点，并返回该节点的系数

int CheckInputErrors(int* xishu_a, int* index_b); // 验证输入格式
int check_index(SLNode* head, int i, int b, DataType* num);// 检查链表中是否存在指定指数的节点，如果存在则删除并返回其系数

void SortList(SLNode* head);// 对链表进行排序（根据指数大小）

// 合并两个多项式（链表）并返回结果
SLNode* Twoformula(SLNode* head1, SLNode* head2, int operate);
void CombineLikeTerms(SLNode* head);// 合并同类项，调整链表中的系数
int IsZeroPolynomial(SLNode* head); // 检查多项式是否为零多项式