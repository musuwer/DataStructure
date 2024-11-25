#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
typedef int DataType;
void InsertSort(DataType a[], int n)
//用直接插入法对a[0]--a[n-1]排序
{
	int i, j;
	DataType temp;
	for (i = 0; i < n - 1; i++) {
		temp = a[i + 1];//先暂存ai+1
		j = i;
		//已排好序的部分，大于ai+1的元素依次后移一个位置			
		while(j > -1 && temp <a[j]){
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}
int main() {
	int N;
	scanf("%d", &N);
	int a[N];
	for (int i = 0; i < N; i++) scanf("%d", &a[i]);
	InsertSort(a, N);
	for (int i = 0; i < N; i++) printf("%d ", a[i]);
}