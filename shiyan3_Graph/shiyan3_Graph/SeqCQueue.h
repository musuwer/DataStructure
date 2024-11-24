#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MaxQueueSize 100  // ջ���������
typedef struct Queue_Node {
	char data;               // ������
	struct Queue_Node* leftChild;  // ������
	struct Queue_Node* rightChild; // ������
} BiTreeQueue_Node;
typedef BiTreeQueue_Node* Queue_DataType;

typedef struct SequenceCyclicQueue {
	Queue_DataType queue[MaxQueueSize];
	int rear;  //��βָ��
	int front;  //��ͷָ��
	int count;  //������
} SeqCQueue;

void QueueInitiate(SeqCQueue* Q) {
	Q->rear = 0;
	Q->front = 0;
	Q->count = 0;
}

//�ж�ѭ������Q�ǿշ񣬷ǿ��򷵻�1�����򷵻�0
int QueueNotEmpty(SeqCQueue Q) {
	return Q.count != 0;
}

int QueueAppend(SeqCQueue* Q, Queue_DataType x) {
	if (Q->count == MaxQueueSize) {
		printf("���������޷�����! \n");
		return 0;
	}
	else {
		Q->queue[Q->rear] = x;
		Q->rear = (Q->rear + 1) % MaxQueueSize;
		Q->count++;
		return 1;
	}
}
int QueueDelete(SeqCQueue* Q, Queue_DataType* d) {
	if (Q->count == 0) {
		printf("�����ѿ�������Ԫ�س�����! \n");
		return 0;
	}
	else {
		*d = Q->queue[Q->front];
		Q->front = (Q->front + 1) % MaxQueueSize;
		Q->count--;
		return 1;
	}
}
int QueueGet(SeqCQueue Q, Queue_DataType* d) {
	if (Q.count == 0) {
		printf("�����ѿ�������Ԫ�ؿ�ȡ! \n");
		return 0;
	}
	else {
		*d = Q.queue[Q.front];
		return 1;
	}
}

