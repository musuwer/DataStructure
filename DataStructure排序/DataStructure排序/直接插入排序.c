#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
typedef int DataType;
void InsertSort(DataType a[], int n)
//��ֱ�Ӳ��뷨��a[0]--a[n-1]����
{
	int i, j;
	DataType temp;
	for (i = 0; i < n - 1; i++) {
		temp = a[i + 1];//���ݴ�ai+1
		j = i;
		//���ź���Ĳ��֣�����ai+1��Ԫ�����κ���һ��λ��			
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