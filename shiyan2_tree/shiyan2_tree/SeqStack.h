#include <stdio.h>
#include <stdlib.h>
#define MaxStackSize 100  // ջ���������

typedef struct Stack_Node {
    char data;               // ������
    struct Stack_Node* leftChild;  // ������
    struct Stack_Node* rightChild; // ������
} BiTreeStack_Node;
typedef BiTreeStack_Node* Stack_DataType;

typedef struct {
    Stack_DataType stack[MaxStackSize];
    int top; //ָ��ջ��Ԫ�صĺ�һ��λ��
} SeqStack;

void StackInitiate(SeqStack* S) {
    S->top = 0;
}

int StackNotEmpty(SeqStack S) {
    if (S.top <= 0)	return 0;
    else return 1;
}

//������Ԫ��ֵx����˳���ջS�У���ջ�ɹ��򷵻�1�����򷵻�0
int StackPush(SeqStack* S, Stack_DataType x) {
    if (S->top >= MaxStackSize) {
        printf("��ջ�����޷�����! \n");
        return 0;
    }
    else {
        S->stack[S->top] = x;
        S->top++;
        return 1;
    }
}
int StackPop(SeqStack* S, Stack_DataType* d) {
    if (S->top <= 0) {
        printf("��ջ�ѿ�������Ԫ�س�ջ! \n");
        return 0;
    }
    else {
        S->top--;
        *d = S->stack[S->top];
        return 1;
    }
}

int StackTop(SeqStack S, Stack_DataType* d) {
    if (S.top <= 0) {
        printf("��ջ�ѿ�! \n");
        return 0;
    }
    else {
        *d = S.stack[S.top - 1];
        return 1;
    }
}
