#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdlib.h>
typedef char DataType;
#define MaxVertices 100

typedef struct Node
{
	int weight;	  //cost
	int dest;	              /*�ڽӱߵĻ�ͷ�������*/
	struct Node* next;
} Edge;		   /*�ڽӱߵ�����Ľ��ṹ��*/
typedef struct {
	DataType data;	/*��������Ԫ��*/
	int source;		/*�ڽӱߵĻ�β�������*/
	Edge* adj;		/*�ڽӱߵ�ͷָ��*/
} AdjLHeight;	     	/*���������Ԫ�����ͽṹ��*/
typedef struct {
	AdjLHeight a[MaxVertices];	/*�ڽӱ�����*/
	int numOfVerts;			/*�������*/
	int numOfEdges;			/*�߸���*/
} AdjLGraph;				/*ͼ���ڽӱ�ṹ��*/

void AdjInitiate(AdjLGraph* G) {
	int i;
	G->numOfEdges = 0;
	G->numOfVerts = 0;
	for (i = 0; i < MaxVertices; i++) {
		G->a[i].source = i;
		G->a[i].adj = NULL;
	}
}
//��ͼG�еĵ�i��λ�ò��붥������Ԫ��vertex
int InsertVertex(AdjLGraph* G, int i, DataType vertex) {
	if (i >= 0 && i < MaxVertices) {
		G->a[i].data = vertex;
		G->numOfVerts++;
		return 1;
	}
	else {
		printf("����Խ��!\n"); return 0;
	}
}

//��ͼG�м����<v1,v2>�����ò��ͷ����
int InsertEdge(AdjLGraph* G, int v1, int v2, int weight) {
	Edge* p;
	if (v1<0 || v1>G->numOfVerts || v2<0 || v2>G->numOfVerts) {
		printf("����v1��v2����!");
		return 0;
	}
	p = (Edge*)malloc(sizeof(Edge));
	p->dest = v2;
	p->next = G->a[v1].adj;
	p->weight = weight;
	G->a[v1].adj = p;
	G->numOfEdges++;
	return 1;
}

void DeleteEdge(AdjLGraph* G, int v1, int v2) {
	Edge* curr, * pre;
	if (v1 < 0 || v1 >= G->numOfVerts || v2 < 0 || v2 >= G->numOfVerts)
	{
		printf("����v1��v2����!");
		return;
	}
	pre = NULL; 	curr = G->a[v1].adj;
	while (curr != NULL && curr->dest != v2)
	{
		pre = curr;
		curr = curr->next;
	}
	//�ڽӱ�<v1,v2>�ǵ�����ĵ�һ�����
	if (curr != NULL && curr->dest == v2 && pre == NULL)
	{
		G->a[v1].adj = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	//�ڽӱ�<v1,v2>���ǵ�����ĵ�һ�����
	else if (curr != NULL && curr->dest == v2 && pre != NULL)
	{
		pre->next = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	else  printf("��<v1,v2>������!");
}

//ȡͼG�ж���v�ĵ�һ���ڽӶ���
int GetFirstVex(AdjLGraph G, int v) {
	Edge* p;
	if (v<0 || v>G.numOfVerts) {
		printf("����Խ��!");
		return -1;
	}
	p = G.a[v].adj;
	if (p != NULL) return p->dest;
	else return -1;
}

//��ͼ��Ѱ��V1������ڽӶ���V2����һ���ڽӶ���
int GetNextVex(AdjLGraph G, int v1, int v2) {
	Edge* p;
	if (v1<0 || v1>G.numOfVerts || v2<0 || v2>G.numOfVerts) {
		printf("����V1��V2Խ��!");
			return -1;
	}
	p = G.a[v1].adj;
	while (p != NULL) {
		if (p->dest != v2)
			p = p->next;
		else break;
	}
	if (p != NULL && p->next != NULL) return p->next->dest;
	else return -1;
}
//����G�����е�����ռ�õĴ洢�ռ�
void AdjDestroy(AdjLGraph* G) {
	int i;
	Edge* p, * q;
	for (i = 0; i < G->numOfVerts; i++) {
		p = G->a[i].adj;
		while (p != NULL) {
			q = p->next;
			free(p);
			p = q;
		}
	}
}
