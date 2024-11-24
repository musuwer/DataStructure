#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct Node {
    DataType data;
    struct Node* next;
} SLNode;

typedef struct {
    SLNode* rear;  // 队尾指针
} LQueue;

// 初始化队列
void QueueInitiate(LQueue* Q) {
    Q->rear = (SLNode*)malloc(sizeof(SLNode));  // 创建头节点
    if (Q->rear == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    Q->rear->next = Q->rear; // 头节点的next指向自己
}

// 添加元素到队列
void QueueAppend(LQueue* Q, DataType x) {
    SLNode* p = (SLNode*)malloc(sizeof(SLNode));
    if (p == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    p->data = x;
    p->next = Q->rear->next; // 新节点指向队头

    // 当队列非空时，队尾加入节点
    Q->rear->next = p;
    Q->rear = p; // 更新队尾指针
}

// 从队列删除元素
int QueueDelete(LQueue* Q, DataType* d) {
    if (Q->rear->next == Q->rear) { // 检查队列是否为空
        printf("队列中已无元素出队列！\n");
        return 0;
    }

    SLNode* p = Q->rear->next; // 队头节点
    *d = p->next->data;               // 获取队头数据

    if (p == Q->rear) {         // 如果只有一个元素
        Q->rear->next = Q->rear; // 队列置空，队尾指向头节点
        Q->rear = Q->rear;      // 队尾也指向头节点
    }
    else {
        Q->rear->next = p->next; // 移动队头指针
    }

    free(p);  // 释放队头节点
    return 1;  // 成功出队
}

// 获取队列的头元素但不删除
int QueueGet(LQueue Q, DataType* d) {
    if (Q.rear->next == Q.rear) {
        printf("队列已经空无元素可取！\n");
        return 0;
    }
    else {
        *d = Q.rear->data; // 返回队头的数据
        return 1;
    }
}
int main() {
    LQueue queue;
    QueueInitiate(&queue);
    int i, j;
    // 向队列添加元素
    for (i = 0; i < 5; i++) {
        QueueAppend(&queue, i);
        QueueGet(queue, &j);
        printf("获取元素: %d\n", j); // 正确打印队尾元素
    
    }
    // 删除队列中的元素并打印
    DataType value;
    while (QueueDelete(&queue, &value)) {
        printf("删除元素:%d\n", value);
    }
    return 0;
}