#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <malloc.h>
#define MaxQueueSize 100
typedef int DataType;
typedef struct qnode {
	DataType data;
	struct qnode* next;
} LQNode;

typedef struct {
	LQNode* front; //��ͷָ��
	LQNode* rear;  //��βָ��
}LQueue;

void QueueInitiate(LQueue* Q) {
	Q->rear = NULL;
	Q->front = NULL;
}

int QueueEmpty(LQueue Q) {
	if (Q.front == NULL) return 0;
	else return 1;
}
void QueueAppend(LQueue* Q, DataType x) {
	LQNode* p;
	p = (LQNode*)malloc(sizeof(LQNode));
	p->data = x;
	p->next = NULL;
	if (Q->rear != NULL) Q->rear->next = p;  //����Ϊ�ǿ�ʱ����β����ڵ�
	Q->rear = p;				//�޸Ķ�βָ��
	if (Q->front == NULL) Q->front = p; //����Ϊ��ʱ����ͷָ���޸�
}

int QueueDelete(LQueue* Q, DataType *d) {
	LQNode* p;
	if (Q->front == NULL) {
		printf("����������Ԫ�س����У�\n");
		return 0;
	}
	else {
		*d = Q->front->data;
		p = Q->front;
		Q->front = Q->front->next;//��ͷ��ǰ��
		if (Q->front == NULL) Q->rear = NULL; //ɾ�����һ��Ԫ�ص�ʱ�򣬶�β�ÿ�

		free(p);
		return 1;
	}
}
int QueueGet(LQueue Q, DataType* d) {
	if (Q.front == NULL) {
		printf("�����Ѿ�����Ԫ�ؿ�ȡ��\n");
		return 0;
	}
	else {
		*d = Q.front->data;
		return 1;
	}
}
int main(){}