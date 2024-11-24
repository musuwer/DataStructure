#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdlib.h>
typedef char DataType;
#define MaxVertices 100

typedef struct Node
{
	int weight;	  //cost
	int dest;	              /*邻接边的弧头顶点序号*/
	struct Node* next;
} Edge;		   /*邻接边单链表的结点结构体*/
typedef struct {
	DataType data;	/*顶点数据元素*/
	int source;		/*邻接边的弧尾顶点序号*/
	Edge* adj;		/*邻接边的头指针*/
} AdjLHeight;	     	/*数组的数据元素类型结构体*/
typedef struct {
	AdjLHeight a[MaxVertices];	/*邻接表数组*/
	int numOfVerts;			/*顶点个数*/
	int numOfEdges;			/*边个数*/
} AdjLGraph;				/*图的邻接表结构体*/

void AdjInitiate(AdjLGraph* G) {
	int i;
	G->numOfEdges = 0;
	G->numOfVerts = 0;
	for (i = 0; i < MaxVertices; i++) {
		G->a[i].source = i;
		G->a[i].adj = NULL;
	}
}
//在图G中的第i个位置插入顶点数据元素vertex
int InsertVertex(AdjLGraph* G, int i, DataType vertex) {
	if (i >= 0 && i < MaxVertices) {
		G->a[i].data = vertex;
		G->numOfVerts++;
		return 1;
	}
	else {
		printf("顶点越界!\n"); return 0;
	}
}

//在图G中加入边<v1,v2>，采用插表头方法
int InsertEdge(AdjLGraph* G, int v1, int v2, int weight) {
	Edge* p;
	if (v1<0 || v1>G->numOfVerts || v2<0 || v2>G->numOfVerts) {
		printf("参数v1或v2出错!");
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
		printf("参数v1或v2出错!");
		return;
	}
	pre = NULL; 	curr = G->a[v1].adj;
	while (curr != NULL && curr->dest != v2)
	{
		pre = curr;
		curr = curr->next;
	}
	//邻接边<v1,v2>是单链表的第一个结点
	if (curr != NULL && curr->dest == v2 && pre == NULL)
	{
		G->a[v1].adj = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	//邻接边<v1,v2>不是单链表的第一个结点
	else if (curr != NULL && curr->dest == v2 && pre != NULL)
	{
		pre->next = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	else  printf("边<v1,v2>不存在!");
}

//取图G中顶点v的第一个邻接顶点
int GetFirstVex(AdjLGraph G, int v) {
	Edge* p;
	if (v<0 || v>G.numOfVerts) {
		printf("顶点越界!");
		return -1;
	}
	p = G.a[v].adj;
	if (p != NULL) return p->dest;
	else return -1;
}

//在图中寻找V1顶点的邻接顶点V2的下一个邻接顶点
int GetNextVex(AdjLGraph G, int v1, int v2) {
	Edge* p;
	if (v1<0 || v1>G.numOfVerts || v2<0 || v2>G.numOfVerts) {
		printf("参数V1或V2越界!");
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
//撤销G中所有单链表占用的存储空间
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
