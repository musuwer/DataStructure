#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#define MaxQueueSize 100
typedef int DataType;

typedef struct {
	DataType queue[MaxQueueSize];
	int rear;
	int front;
	int count;
}SeqCQueue; //顺序循环队列

//初始化队列
void QueueInitiate(SeqCQueue* Q) {
	Q->rear = 0;   //尾部
	Q->front = 0;  //头部
	Q->count = 0;  //数目
}

//检查是否队列为空
int QueueNotEmpty(SeqCQueue Q) {
	if (Q.count != 0) return 1;
	else return 0;
}

//入队列
int QueueAppend(SeqCQueue* Q, DataType x) {
	if (Q->count > 0 && Q->rear == Q->front) {
		printf("队列已经插满无法插入数据！\n");
		return 0;
	}
	else {
		Q->queue[Q->rear] = x;  //rear为当前插入的位置，队尾的下一个点
		Q->rear = (Q->rear + 1) % MaxQueueSize; //队尾指针加一且是循环结构
		Q->count++;
		return 1;
	}
}

//出队列
int QueueDelete(SeqCQueue* Q, DataType* d) {
	if (Q->count == 0) {
		printf("队列已经空了无元素出列！\n");
		return 0;
	}
	else {
		*d = Q->queue[Q->front];
		Q->front = (Q->front + 1) % MaxQueueSize;
		Q->count--;
		return 1;
	}
}

int QueueGet(SeqCQueue Q, DataType* d) {
	if (Q.count == 0) {
		printf("队列已空无元素可取!\n");
		return 0;
	}
	else {
		*d = Q.queue[Q.front];
		return 1;
	}
}


int main() {}