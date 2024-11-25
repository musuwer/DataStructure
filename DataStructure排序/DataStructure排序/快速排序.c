#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdio.h>
typedef int DataType;
void quick_sort(int a[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = a[l];
    while (i < j) {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    quick_sort(a, l, j);
    quick_sort(a, j + 1, r);
}
void QuickSort(DataType a[], int low, int high) {
    int i = low, j = high;
    DataType temp = a[low];
    while (i < j) {
        while (i < j && temp <= a[j]) j--; //在数组的右端扫描
        if (i < j) {
            a[i] = a[j];
            i++;
        }
        while (i < j && a[i] < temp) i++; //在数组的左端扫描
        if (i < j) {
            a[j] = a[i];
            j--;
        }
    }
    a[i] = temp; //重合的位置放枢轴
    if (low < i) QuickSort(a, low, i - 1);
    if (i < high) QuickSort(a, j + 1, high);
}

int main() {
    int N;
    scanf("%d", &N);
    int a[N];
    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    quick_sort(a, 0, N - 1);
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
}