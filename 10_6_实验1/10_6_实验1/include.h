#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h>
#include <malloc.h> // ������̬�ڴ�����ͷ�ļ�

typedef int DataType;// ������������Ϊ����

// ��������ڵ�ṹ��
typedef struct Node {
    DataType xishu; // ϵ��
    DataType index; // ָ��
    struct Node* next; // ָ����һ���ڵ��ָ��
} SLNode, * LinkList; 

void ListInitiate(LinkList* head);// ��ʼ����������һ��ͷ�ڵ�
int ListLength(SLNode* head);// ��ȡ����ĳ���
int ListInsert(SLNode* head, int i, DataType a, DataType b);// ������ָ��λ�ò����½ڵ�
int ListGet(SLNode* head, int i, DataType* x, DataType* y);// ��ȡ������ָ��λ�õĽڵ��ϵ����ָ��
int ListDelete(SLNode* head, int i, DataType* x);// ɾ��������ָ��λ�õĽڵ㣬�����ظýڵ��ϵ��

int CheckInputErrors(int* xishu_a, int* index_b); // ��֤�����ʽ
int check_index(SLNode* head, int i, int b, DataType* num);// ����������Ƿ����ָ��ָ���Ľڵ㣬���������ɾ����������ϵ��

void SortList(SLNode* head);// ������������򣨸���ָ����С��

// �ϲ���������ʽ�����������ؽ��
SLNode* Twoformula(SLNode* head1, SLNode* head2, int operate);
void CombineLikeTerms(SLNode* head);// �ϲ�ͬ������������е�ϵ��
int IsZeroPolynomial(SLNode* head); // ������ʽ�Ƿ�Ϊ�����ʽ