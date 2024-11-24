#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#define MaxQueueSize 100
typedef int DataType;

typedef struct {
	DataType queue[MaxQueueSize];
	int front;
	int count;
}SeqCQueue; //˳��ѭ������

//��ʼ������
void QueueInitiate(SeqCQueue* Q) {
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
	if (Q->count == MaxQueueSize) {
		printf("�����Ѿ������޷��������ݣ�\n");
		return 0;
	}
	else {
		Q->queue[Q->front] = x;  //frontΪ��ǰ�����λ�ã���β����һ����
		Q->front = (Q->front + 1) % MaxQueueSize; //��βָ���һ����ѭ���ṹ
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
//��ȡͷԪ��
int QueueGet(SeqCQueue Q, DataType* d) {
	if (Q.count == 0) {
		printf("�����ѿ���Ԫ�ؿ�ȡ!\n");
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
    QueueInitiate(&Q); // ��ʼ������

    // �������
    for (int i = 1; i <= 10; i++) {
        printf("���Ԫ��: %d\n", i);
        QueueAppend(&Q, i);
    }
	
    // ���Ի�ȡ��ͷԪ��
    DataType frontElement;
    if (QueueGet(Q, &frontElement)) {
        printf("��ͷԪ��: %d\n", frontElement);
    }

    // ���Գ���
    DataType deletedElement;
    for (int i = 0; i < 5; i++) {
        if (QueueDelete(&Q, &deletedElement)) {
            printf("����Ԫ��: %d\n", deletedElement);
        }
    }

    // �ٴλ�ȡ��ͷԪ��
    if (QueueGet(Q, &frontElement)) {
        printf("�µĶ�ͷԪ��: %d\n", frontElement);
    }
    // ���Լ�������
    while (QueueDelete(&Q, &deletedElement)) {
        printf("����Ԫ��: %d\n", deletedElement);
    }

    return 0;
}