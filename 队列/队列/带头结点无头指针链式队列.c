#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct Node {
    DataType data;
    struct Node* next;
} SLNode;

typedef struct {
    SLNode* rear;  // ��βָ��
} LQueue;

// ��ʼ������
void QueueInitiate(LQueue* Q) {
    Q->rear = (SLNode*)malloc(sizeof(SLNode));  // ����ͷ�ڵ�
    if (Q->rear == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    Q->rear->next = Q->rear; // ͷ�ڵ��nextָ���Լ�
}

// ���Ԫ�ص�����
void QueueAppend(LQueue* Q, DataType x) {
    SLNode* p = (SLNode*)malloc(sizeof(SLNode));
    if (p == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }
    p->data = x;
    p->next = Q->rear->next; // �½ڵ�ָ���ͷ

    // �����зǿ�ʱ����β����ڵ�
    Q->rear->next = p;
    Q->rear = p; // ���¶�βָ��
}

// �Ӷ���ɾ��Ԫ��
int QueueDelete(LQueue* Q, DataType* d) {
    if (Q->rear->next == Q->rear) { // �������Ƿ�Ϊ��
        printf("����������Ԫ�س����У�\n");
        return 0;
    }

    SLNode* p = Q->rear->next; // ��ͷ�ڵ�
    *d = p->next->data;               // ��ȡ��ͷ����

    if (p == Q->rear) {         // ���ֻ��һ��Ԫ��
        Q->rear->next = Q->rear; // �����ÿգ���βָ��ͷ�ڵ�
        Q->rear = Q->rear;      // ��βҲָ��ͷ�ڵ�
    }
    else {
        Q->rear->next = p->next; // �ƶ���ͷָ��
    }

    free(p);  // �ͷŶ�ͷ�ڵ�
    return 1;  // �ɹ�����
}

// ��ȡ���е�ͷԪ�ص���ɾ��
int QueueGet(LQueue Q, DataType* d) {
    if (Q.rear->next == Q.rear) {
        printf("�����Ѿ�����Ԫ�ؿ�ȡ��\n");
        return 0;
    }
    else {
        *d = Q.rear->data; // ���ض�ͷ������
        return 1;
    }
}
int main() {
    LQueue queue;
    QueueInitiate(&queue);
    int i, j;
    // ��������Ԫ��
    for (i = 0; i < 5; i++) {
        QueueAppend(&queue, i);
        QueueGet(queue, &j);
        printf("��ȡԪ��: %d\n", j); // ��ȷ��ӡ��βԪ��
    
    }
    // ɾ�������е�Ԫ�ز���ӡ
    DataType value;
    while (QueueDelete(&queue, &value)) {
        printf("ɾ��Ԫ��:%d\n", value);
    }
    return 0;
}