#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <malloc.h>
typedef int DataType;

typedef struct Node {
    DataType xishu; // 系数
    DataType index; // 指数
    struct Node* next;
} SLNode, * LinkList;

void ListInitiate(LinkList* head) {
    *head = (SLNode*)malloc(sizeof(SLNode));
    if (*head == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    (*head)->next = NULL;
}

int ListLength(SLNode* head) {
    SLNode* p = head->next;
    int num = 0;
    while (p != NULL) {
        num++;
        p = p->next;
    }
    return num;
}

int ListInsert(SLNode* head, int i, DataType a, DataType b) {
    SLNode* p, * q;
    p = head;
    int j = -1;
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (j != i - 1) {
        printf("插入元素位置错误\n");
        return 0;
    }
    q = (SLNode*)malloc(sizeof(SLNode));
    if (q == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }
    q->xishu = a;
    q->index = b;

    q->next = p->next;
    p->next = q;
    return 1;
}

int ListGet(SLNode* head, int i, DataType* x, DataType* y)
{
    SLNode* p;
    int j;
    p = head;
    j = -1;
    while (p->next != NULL && j < i) {
        p = p->next;
        j++;
    }
    if (j != i) {
        printf("取出的元素位置参数错误！\n");
        return 0;
    }
    *x = p->xishu; // 获取系数
    *y = p->index; // 获取指数
    return 1;
}

int ListDelete(SLNode* head, int i, DataType* x) {
    SLNode* p, * s;
    int j = -1;
    p = head;
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p->next == NULL) {
        printf("要删除的节点不存在！\n");
        return 0;
    }
    s = p->next;
    *x = s->xishu;

    p->next = s->next;
    free(s);
    return 1;
}

int check_index(SLNode* head, int i, int b, DataType* num) { // 若指数相同则进行相加
    SLNode* p = head->next;
    int j = 0; // 从 0 开始
    while (p != NULL) {
        if (p->index == b) { // 使用比较操作符
            ListDelete(head, j, num);
            return 1;
        }
        p = p->next;
        j++;
    }
    *num = 0;
    return 0;
}

// 排序链表（根据指数大小）
void SortList(SLNode* head) {
    if (head == NULL || head->next == NULL) return;

    SLNode* current, * index;
    DataType tempX, tempY;

    for (current = head->next; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->index > index->index) { // 根据指数进行比较
                // 交换系数和指数
                tempX = current->xishu;
                tempY = current->index;
                current->xishu = index->xishu;
                current->index = index->index;
                index->xishu = tempX;
                index->index = tempY;
            }
        }
    }
}

int main() {
    SLNode* head;
    int i;
    int a, b; // 接收系数和指数进行检验
    DataType num = 0; // 接收指数相同时候的系数进行相加
    ListInitiate(&head);

    printf("以（系数，指数）方式输入:\n");
    for (i = 0; i < 3; i++) {
        printf("输入第 %d 项：", i + 1);
        scanf("%d,%d", &a, &b);

        // 检查是否已有相同指数的节点
        if (check_index(head, i, b, &num)) {
            ListInsert(head, ListLength(head), a + num, b); // 在链表末尾插入新节点
        }
        else {
            // 如果没有相同的指数，则直接插入
            ListInsert(head, ListLength(head), a, b);
        }
    }
    SortList(head);
    printf("输入数据完成，检验\n");
    for (i = 0; i < ListLength(head); i++) {
        DataType x ,y;
        ListGet(head, i, &x, &y);
        printf("1+%dx^%d", x, y); // 检查系数是否正确存入链表中
        if (i != ListLength(head) - 1) printf("+");
    }
    return 0;
}