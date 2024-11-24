#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#define MaxQueueSize 100
typedef int DataType;

typedef struct {
	DataType queue[MaxQueueSize];
	int front;
	int count;
}SeqCQueue; //顺序循环队列

//初始化队列
void QueueInitiate(SeqCQueue* Q) {
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
	if (Q->count == MaxQueueSize) {
		printf("队列已经插满无法插入数据！\n");
		return 0;
	}
	else {
		Q->queue[Q->front] = x;  //front为当前插入的位置，队尾的下一个点
		Q->front = (Q->front + 1) % MaxQueueSize; //队尾指针加一且是循环结构
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
		int count = Q->count;
		int front = Q->front; 
		while (count > 0) {
			if (front - 1 < 0) front = MaxQueueSize - 1;
			else front--;
			count--;
		}
		*d = Q->queue[front];
		Q->count--;
		return 1;
	}
}
//获取头元素
int QueueGet(SeqCQueue Q, DataType* d) {
	if (Q.count == 0) {
		printf("队列已空无元素可取!\n");
		return 0;
	}
	else {

		while (Q.count > 0) {
			if (Q.front - 1 < 0) Q.front = MaxQueueSize - 1;
			else Q.front--;
			Q.count--;
		}
	}
	*d = Q.queue[Q.front];
	return 1;
}

int main() {
    SeqCQueue Q;
    QueueInitiate(&Q); // 初始化队列

    // 测试入队
    for (int i = 1; i <= 10; i++) {
        printf("入队元素: %d\n", i);
        QueueAppend(&Q, i);
    }
	
    // 测试获取队头元素
    DataType frontElement;
    if (QueueGet(Q, &frontElement)) {
        printf("队头元素: %d\n", frontElement);
    }

    // 测试出队
    DataType deletedElement;
    for (int i = 0; i < 5; i++) {
        if (QueueDelete(&Q, &deletedElement)) {
            printf("出队元素: %d\n", deletedElement);
        }
    }

    // 再次获取队头元素
    if (QueueGet(Q, &frontElement)) {
        printf("新的队头元素: %d\n", frontElement);
    }
    // 测试继续出队
    while (QueueDelete(&Q, &deletedElement)) {
        printf("出队元素: %d\n", deletedElement);
    }

    return 0;
}