#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct {
    char* data;   // �洢���ݵĶ�̬����
    int size;     // ��ǰԪ������
    int capacity; // ��������
} OrderedList;

void InitList(OrderedList* list);// ��ʼ������˳���
int GetSize(OrderedList* list);// ��ȡ����Ԫ�ظ���
void ListInsert(OrderedList* list, char x);// ����Ԫ�أ���������
void ListDelete(OrderedList* list, char x);// ɾ��Ԫ��
char GetElement(OrderedList* list, int index);// ��ȡ����Ԫ��
void ListMerge(OrderedList* L1, OrderedList* L2, OrderedList* L3);// �ϲ���������˳���
void FreeList(OrderedList* list);// �ͷ��ڴ�