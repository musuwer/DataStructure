#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10

typedef struct {
    char* data;   // 存储数据的动态数组
    int size;     // 当前元素数量
    int capacity; // 数组容量
} OrderedList;

void InitList(OrderedList* list);// 初始化有序顺序表
int GetSize(OrderedList* list);// 获取数据元素个数
void ListInsert(OrderedList* list, char x);// 插入元素（保持有序）
void ListDelete(OrderedList* list, char x);// 删除元素
char GetElement(OrderedList* list, int index);// 获取数据元素
void ListMerge(OrderedList* L1, OrderedList* L2, OrderedList* L3);// 合并两个有序顺序表
void FreeList(OrderedList* list);// 释放内存