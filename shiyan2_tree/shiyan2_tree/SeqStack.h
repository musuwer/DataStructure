#include <stdio.h>
#include <stdlib.h>
#define MaxStackSize 100  // 栈的最大容量

typedef struct Stack_Node {
    char data;               // 数据域
    struct Stack_Node* leftChild;  // 左子树
    struct Stack_Node* rightChild; // 右子树
} BiTreeStack_Node;
typedef BiTreeStack_Node* Stack_DataType;

typedef struct {
    Stack_DataType stack[MaxStackSize];
    int top; //指向栈顶元素的后一个位置
} SeqStack;

void StackInitiate(SeqStack* S) {
    S->top = 0;
}

int StackNotEmpty(SeqStack S) {
    if (S.top <= 0)	return 0;
    else return 1;
}

//把数据元素值x存入顺序堆栈S中，入栈成功则返回1，否则返回0
int StackPush(SeqStack* S, Stack_DataType x) {
    if (S->top >= MaxStackSize) {
        printf("堆栈已满无法插入! \n");
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
        printf("堆栈已空无数据元素出栈! \n");
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
        printf("堆栈已空! \n");
        return 0;
    }
    else {
        *d = S.stack[S.top - 1];
        return 1;
    }
}
