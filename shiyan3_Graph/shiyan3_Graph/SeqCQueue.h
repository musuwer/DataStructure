#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MaxQueueSize 100  // 栈的最大容量
typedef struct Queue_Node {
	char data;               // 数据域
	struct Queue_Node* leftChild;  // 左子树
	struct Queue_Node* rightChild; // 右子树
} BiTreeQueue_Node;
typedef BiTreeQueue_Node* Queue_DataType;

typedef struct SequenceCyclicQueue {
	Queue_DataType queue[MaxQueueSize];
	int rear;  //队尾指针
	int front;  //队头指针
	int count;  //计数器
} SeqCQueue;

void QueueInitiate(SeqCQueue* Q) {
	Q->rear = 0;
	Q->front = 0;
	Q->count = 0;
}

//判断循环队列Q非空否，非空则返回1，否则返回0
int QueueNotEmpty(SeqCQueue Q) {
	return Q.count != 0;
}

int QueueAppend(SeqCQueue* Q, Queue_DataType x) {
	if (Q->count == MaxQueueSize) {
		printf("队列已满无法插入! \n");
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
		printf("队列已空无数据元素出队列! \n");
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
		printf("队列已空无数据元素可取! \n");
		return 0;
	}
	else {
		*d = Q.queue[Q.front];
		return 1;
	}
}

