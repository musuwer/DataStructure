#include "OrderedList.h"

void InitList(OrderedList* list) {
    list->size = 0;
    list->capacity = INITIAL_SIZE;
    list->data = (char*)malloc(list->capacity * sizeof(char));
}

int GetSize(OrderedList* list) {
    return list->size;
}

void ListInsert(OrderedList* list, char x) {
    int i;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->data = (char*)realloc(list->data, list->capacity * sizeof(char));
    }
    for (i = list->size - 1; (i >= 0 && list->data[i] > x); i--) {
        list->data[i + 1] = list->data[i]; // ����ƶ�Ԫ��
    }
    list->data[i + 1] = x; // ����Ԫ��
    list->size++;
}

void ListDelete(OrderedList* list, char x) {
    int i;
    for (i = 0; i < list->size; i++) {
        if (list->data[i] == x) {
            for (int j = i; j < list->size - 1; j++) {
                list->data[j] = list->data[j + 1]; // ��ǰ�ƶ�Ԫ��
            }
            list->size--;
            return;
        }
    }
}

char GetElement(OrderedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("����Խ��\n");
        return '\0'; // ���ؿ��ַ�
    }
    return list->data[index];
}

void ListMerge(OrderedList* L1, OrderedList* L2, OrderedList* L3) {
    L3->size = 0;
    L3->capacity = L1->size + L2->size;
    L3->data = (char*)malloc(L3->capacity * sizeof(char));

    int i = 0, j = 0;
    while (i < L1->size && j < L2->size) {
        if (L1->data[i] < L2->data[j]) {
            L3->data[L3->size++] = L1->data[i++];
        }
        else {
            L3->data[L3->size++] = L2->data[j++];
        }
    }

    while (i < L1->size) {
        L3->data[L3->size++] = L1->data[i++];
    }

    while (j < L2->size) {
        L3->data[L3->size++] = L2->data[j++];
    }
}

void FreeList(OrderedList* list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}
int main() {
    OrderedList list1, list2, mergedList;
    InitList(&list1);
    InitList(&list2);
    InitList(&mergedList);

    // �������ݵ� list1
    char data1[] = { 'c', 'h', 'a', 'i', 'c', 'h', 'e', 'n', 'g' };
    for (int i = 0; i < sizeof(data1); i++) {
        ListInsert(&list1, data1[i]);
    }

    // �������ݵ� list2
    char data2[] = { 'y', 'u', 'a', 'n' };
    for (int i = 0; i < sizeof(data2); i++) {
        ListInsert(&list2, data2[i]);
    }

    // ��ӡ list1 �е�Ԫ��
    printf("list1 �е�Ԫ�أ�");
    for (int i = 0; i < GetSize(&list1); i++) {
        printf("%c ", GetElement(&list1, i));
    }
    printf("\n");

    // ��ӡ list2 �е�Ԫ��
    printf("list2 �е�Ԫ�أ�");
    for (int i = 0; i < GetSize(&list2); i++) {
        printf("%c ", GetElement(&list2, i));
    }
    printf("\n");

    // �ϲ� list1 �� list2
    ListMerge(&list1, &list2, &mergedList);

    // ��ӡ�ϲ���Ľ��
    printf("�ϲ��������˳���");
    for (int i = 0; i < GetSize(&mergedList); i++) {
        printf("%c ", GetElement(&mergedList, i));
    }
    printf("\n");

    // �ͷ��ڴ�
    FreeList(&list1);
    FreeList(&list2);
    FreeList(&mergedList);

    return 0;
}