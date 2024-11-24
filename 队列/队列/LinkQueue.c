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
	LQNode* front; //队头指针
	LQNode* rear;  //队尾指针
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
	if (Q->rear != NULL) Q->rear->next = p;  //队列为非空时，队尾加入节点
	Q->rear = p;				//修改队尾指针
	if (Q->front == NULL) Q->front = p; //队列为空时，队头指针修改
}

int QueueDelete(LQueue* Q, DataType *d) {
	LQNode* p;
	if (Q->front == NULL) {
		printf("队列中已无元素出队列！\n");
		return 0;
	}
	else {
		*d = Q->front->data;
		p = Q->front;
		Q->front = Q->front->next;//队头往前移
		if (Q->front == NULL) Q->rear = NULL; //删除最后一个元素的时候，队尾置空

		free(p);
		return 1;
	}
}
int QueueGet(LQueue Q, DataType* d) {
	if (Q.front == NULL) {
		printf("队列已经空无元素可取！\n");
		return 0;
	}
	else {
		*d = Q.front->data;
		return 1;
	}
}
int main(){}