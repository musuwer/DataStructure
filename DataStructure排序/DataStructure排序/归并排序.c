#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//int tmp[10000];
//// 归并排序的实现
//void merge_sort(int q[], int l, int r)
//{
//    if (l >= r) return;
//    int mid = (l + r) / 2;
//    merge_sort(q, l, mid);
//    merge_sort(q, mid + 1, r);
//
//    int k = 0, i = l, j = mid + 1;
//    while (i <= mid && j <= r)
//        if (q[i] <= q[j]) tmp[k++] = q[i++];
//        else tmp[k++] = q[j++];
//    //对两个数组中剩下的元素直接移动到temp数组中
//    while (i <= mid) tmp[k++] = q[i++];
//    while (j <= r) tmp[k++] = q[j++];
//    for (i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];
//}
//#include<stdio.h>
int temp[10000];
void msort(int q[], int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    msort(q, l, mid);
    msort(q, mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) temp[k++] = q[i++];
        else temp[k++] = q[j++];
    }
    while (i <= mid) temp[k++] = q[i++];
    while (j <= r) temp[k++] = q[j++];
    for (int i = l, j = 0; i <= r; i++, j++)q[i] = temp[j];
}
int main() {
    int N;
    scanf("%d", &N);
    int a[N];
    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    msort(a, 0, N - 1);
    for (int i = 0; i < N; i++)printf("%d ", a[i]);
}
//int main(){
//    int N;
//    scanf("%d", &N);
//    int a[N];
//    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
//    merge_sort(a, 0, N - 1);
//    for (int i = 0; i < N; i++) printf("%d ", a[i]);
//}