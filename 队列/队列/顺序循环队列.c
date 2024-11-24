#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#define MaxQueueSize 100
typedef int DataType;

typedef struct {
	DataType queue[MaxQueueSize];
	int rear;
	int front;
	int count;
}SeqCQueue; //˳��ѭ������

//��ʼ������
void QueueInitiate(SeqCQueue* Q) {
	Q->rear = 0;   //β��
	Q->front = 0;  //ͷ��
	Q->count = 0;  //��Ŀ
}

//����Ƿ����Ϊ��
int QueueNotEmpty(SeqCQueue Q) {
	if (Q.count != 0) return 1;
	else return 0;
}

//�����
int QueueAppend(SeqCQueue* Q, DataType x) {
	if (Q->count > 0 && Q->rear == Q->front) {
		printf("�����Ѿ������޷��������ݣ�\n");
		return 0;
	}
	else {
		Q->queue[Q->rear] = x;  //rearΪ��ǰ�����λ�ã���β����һ����
		Q->rear = (Q->rear + 1) % MaxQueueSize; //��βָ���һ����ѭ���ṹ
		Q->count++;
		return 1;
	}
}

//������
int QueueDelete(SeqCQueue* Q, DataType* d) {
	if (Q->count == 0) {
		printf("�����Ѿ�������Ԫ�س��У�\n");
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
		printf("�����ѿ���Ԫ�ؿ�ȡ!\n");
		return 0;
	}
	else {
		*d = Q.queue[Q.front];
		return 1;
	}
}


int main() {}