#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <malloc.h>
typedef int DataType;

typedef struct Node {
    DataType xishu; // ϵ��
    DataType index; // ָ��
    struct Node* next;
} SLNode, * LinkList;

void ListInitiate(LinkList* head) {
    *head = (SLNode*)malloc(sizeof(SLNode));
    if (*head == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
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
        printf("����Ԫ��λ�ô���\n");
        return 0;
    }
    q = (SLNode*)malloc(sizeof(SLNode));
    if (q == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
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
        printf("ȡ����Ԫ��λ�ò�������\n");
        return 0;
    }
    *x = p->xishu; // ��ȡϵ��
    *y = p->index; // ��ȡָ��
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
        printf("Ҫɾ���Ľڵ㲻���ڣ�\n");
        return 0;
    }
    s = p->next;
    *x = s->xishu;

    p->next = s->next;
    free(s);
    return 1;
}

int check_index(SLNode* head, int i, int b, DataType* num) { // ��ָ����ͬ��������
    SLNode* p = head->next;
    int j = 0; // �� 0 ��ʼ
    while (p != NULL) {
        if (p->index == b) { // ʹ�ñȽϲ�����
            ListDelete(head, j, num);
            return 1;
        }
        p = p->next;
        j++;
    }
    *num = 0;
    return 0;
}

// ������������ָ����С��
void SortList(SLNode* head) {
    if (head == NULL || head->next == NULL) return;

    SLNode* current, * index;
    DataType tempX, tempY;

    for (current = head->next; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->index > index->index) { // ����ָ�����бȽ�
                // ����ϵ����ָ��
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
    int a, b; // ����ϵ����ָ�����м���
    DataType num = 0; // ����ָ����ͬʱ���ϵ���������
    ListInitiate(&head);

    printf("�ԣ�ϵ����ָ������ʽ����:\n");
    for (i = 0; i < 3; i++) {
        printf("����� %d �", i + 1);
        scanf("%d,%d", &a, &b);

        // ����Ƿ�������ָͬ���Ľڵ�
        if (check_index(head, i, b, &num)) {
            ListInsert(head, ListLength(head), a + num, b); // ������ĩβ�����½ڵ�
        }
        else {
            // ���û����ͬ��ָ������ֱ�Ӳ���
            ListInsert(head, ListLength(head), a, b);
        }
    }
    SortList(head);
    printf("����������ɣ�����\n");
    for (i = 0; i < ListLength(head); i++) {
        DataType x ,y;
        ListGet(head, i, &x, &y);
        printf("1+%dx^%d", x, y); // ���ϵ���Ƿ���ȷ����������
        if (i != ListLength(head) - 1) printf("+");
    }
    return 0;
}