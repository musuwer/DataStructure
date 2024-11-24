#define _CRT_SECURE_NO_WARNINGS 1
#define MaxSize 100;

#include<stdio.h>
#include<malloc.h>
typedef int DataType;


typedef struct Node
{
    DataType data;
    struct Node* next;
}SLNode, * LinkList;

void ListInitiate(LinkList* head)
{
    *head = (SLNode*)malloc(sizeof(SLNode));
    (*head)->next = NULL;
}
int ListInsert(SLNode* head, int i, DataType x)
{
    SLNode* p, * q;
    p = head;
    int j = -1;
    while (p->next != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (j != i - 1) {
        printf("c����Ԫ��λ�ô���");
        return 0;
    }
    q = (SLNode*)malloc(sizeof(SLNode));
    q->data = x;

    q->next = p->next;
    p->next = q;
    return 1;
}
int ListDelete(SLNode* head, int i, DataType* x)
{
    SLNode* p, * s;
    int j = -1;
    p = head;
    while (p->next != NULL && p->next->next != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    s = p->next;
    *x = s->data;
    p->next = s->next;
    free(s);
    return 1;
}
int ListGet(SLNode* head, int i, DataType* x)
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
        printf("ȡ����Ԫ��λ�ò�������");
        return 0;
    }
    *x = p->data;
    return 1;
}

int ListLength(SLNode* head)
{
    SLNode* p = head->next;
    int num = 0;
    while (p != NULL)
    {
        num++;
        p = p->next;
    }
    return num;
}
int main()
{
    SLNode* head;
    int i, x;
    ListInitiate(&head);
    for (i = 0; i < 10; i++)
        ListInsert(head, i, i + 1);
    ListDelete(head, 5, &x);

    for (i = 0; i < ListLength(head); i++) {
        ListGet(head, i, &x);
        printf("%d\n", x);
    }
    printf("Hello world!");
    return 0;
}
typedef struct
{
    DataType list[MaxSize];
    int size;
} SeqList;


//˳��� 2��16
int ListFind(SeqList* L, DataType x, int i)
{
    int j = 0;
    if (i < 0 || i > L->size - 1)
    {
        printf("ֵ������\n");
        return -1;
    }
    else
    {
        for (j = i; j < L->size; j++)
        {
            if (x == L->list[j])
            {
                return j;
            }
        }
    }
}
//˳���2��17
int List_Orderly_insertion(SeqList* L, DataType x)
{
    int j, i;
    if (L->size >= MaxSize) //
    {
        printf("˳����Ѿ����˲��ܲ���");
        return -1;
    }
    else if (x > L->list[L->size - 1] && L->size < Maxsize)
    {
        L->list[L->size] = x;
        L->size++;
        return 1;
    }
    else
    {
        for (i = 0; i < L->size; i++)
        {
            if (x <= L->list[i])
            {
                for (j = L->size; j > i; j--)  L->list[j] = L->list[j - 1];
                L->list[i] = x;
                L->size++;
                return 1;
            }
        }
        return -1;
    }
}
//����2��19
int ListDeleteMore(SLNode* head, DataTypa x)
{
    SLNode* p, * s;
    int num = 0;
    s = head;   //��ʼ��ָ��
    p = head->next;
    while (p != NULL)
    {
        if (p->data == x)
        {
            num++;
            s->next = p->next;
            free(p);
            p = s->next;
        }
        else
        {
            s = p;
            p = p->next;
        }
    }
    return num;
}
//����2��22
int ListInsert(SLNode** head, int i, DataType x)
{
    SLNode* p, * q;
    int j = 0;
    p = *head;
    q = (SLNode*)malloc(sizeof(SLNode));
    q->data = x;
    if (i == 0) //�����������ͷ������{
        q->next = *head; //�������þֲ�����p������*head
    *head = q;
    return 1;
}
while (p->next != NULL && j < i - 1) {
    p = p->next;
    j++;
}
q->next = p->next;
p->next = q;
return 1;
}
int ListDelete(SLNode** head, int i, DataType* x)
{
    SLNode* p, * s;
    int j = 0;
    if (*head == NULL)
        return -1; //����Ϊ�գ�ɾ��ʧ��
    p = *head;
    if (i == 0) {
        *x = *head->data;
        *head = *head->next;
        free(p);
        return 1;
    }
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (j != i - 1 || p->next == NULL) {
        return -1; //ɾ��λ�ò��Ϸ�
    }
    s = p->next;
    *x = s->data;
    p->next = s->next;
    free(s);
    return 1;
}
