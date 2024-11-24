#pragma once
#define MaxSize 100
typedef char DataType;

typedef  struct slist {
	DataType list[MaxSize];				
	int size;
	int maxlength; 	//��ǰ����Ĵ洢����
} SeqList;

void ListInitiate(SeqList* L)
{
	L->size = 0;  /*�����ʼ����Ԫ�ظ���*/
}

int ListLength(SeqList L) {
	return L.size;
}

int ListInsert(SeqList* L, int i, DataType x) {
	//��˳���L�ĵ�i��0��i �� length����λ��ǰ��������Ԫ��x
	//����ɹ�����1��ʧ�ܷ���0
	int j;
	if (L->size >= MaxSize) {
		printf("˳��������޷����룡\n");
		return 0;
	}
	else if (i<0 || i>L->size) {
		printf("����i���Ϸ�!\n");
		return 0;
	}
	else {
		for (j = L->size; j > i; j--)
			L->list[j] = L->list[j - 1]; 	/*���κ���*/
		L->list[i] = x;			/*����x*/
		L->size++;			/*Ԫ�ظ�����1*/
		return 1;
	}
}

int ListDelete(SeqList* L, int i, DataType* x) {
	//ɾ��˳���L��λ��i��0��i �� length-1���ϵ�����Ԫ�ز����浽x��
	//ɾ���ɹ�����1��ɾ��ʧ�ܷ���0
	int j;
	if (L->size <= 0) {
		printf("˳����ѿ�������Ԫ�ؿ�ɾ��\n");
		return 0;
	}
	else if (i<0 || i>L->size - 1) {
		printf("����i���Ϸ���\n");
		return 0;
	}
	else {
		*x = L->list[i];	/*����ɾ����Ԫ�ص�x��*/
		for (j = i + 1; j <= L->size - 1; j++)
			L->list[j - 1] = L->list[j];      	/*����ǰ��*/
		L->size--;			/*����Ԫ�ظ�����1*/
		return 1;
	}
}

int ListGet(SeqList L, int i, DataType* x) {
	if (i < 0 || i > L.size - 1) {
		printf("����i���Ϸ�! \n");
		return 0;
	}
	else {
		*x = L.list[i];
		return 1;
	}
}

