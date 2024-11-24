#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include "SeqList.h"	
#include <stdlib.h>
#include<limits.h>	//C中常量INT_MAX和INT_MIN分别表示最大、最小整数

typedef char DataType;
#define MaxSize 100
#define MaxVertices 100
#define MaxWeight 0x7f7f7f7f	//INT_MAX= 2^31-1= 0x7fffffff

typedef struct
{
	SeqList Vertices;	//存放顶点的顺序表，vertex的复数
	//存放边的邻接矩阵
	int edge[MaxVertices][MaxVertices];
	int numOfEdges; 	//边的条数
}AdjMGraph;

typedef struct {
	int row;			//行下标
	int col;			//列下标
	int weight;			//权值
} RowColWeight;  		//边信息结构体

//初始化有n个顶点的顶点顺序表和邻接矩阵
void Initiate(AdjMGraph* G, int n) {
	ListInitiate(&G->Vertices);	    /*顺序表初始化*/
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (i == j) G->edge[i][j] = 0;
			else G->edge[i][j] = MaxWeight;
		}
	G->numOfEdges = 0;		/*边的条数置为0*/
}

//在图中增加一个顶点，增加在顶点顺序表的最后
void InsertVertex(AdjMGraph* G, DataType vertex) {
	ListInsert(&G->Vertices, G->Vertices.size, vertex);
}

//在图中增加一条有向边，对于增加一条无向边可通过增加两条有向边完成
int InsertEdge(AdjMGraph* G, int v1, int v2, int weight) {
	if (v1 < 0 || v1 >= G->Vertices.size || v2 < 0
		|| v2 >= G->Vertices.size || v1 == v2) {
		printf("参数v1或v2越界出错!\n");
		return 0;
	}
	if (G->edge[v1][v2] == MaxWeight) { //如果边存在则不修改权值 
		G->edge[v1][v2] = weight;
		G->numOfEdges++;
		return 1;
	}
	return 0;
}

//在图中取消一条有向边
void DeleteEdge(AdjMGraph* G, int v1, int v2) {
	if (v1 < 0 || v1 > G->Vertices.size || v2 < 0
		|| v2 > G->Vertices.size || v1 == v2) {
		printf("参数v1或v2越界出错!\n");
		exit(1);
	}
	if (G->edge[v1][v2] == MaxWeight || v1 == v2) {
		printf("该边不存在!\n");
		exit(0);
	}
	G->edge[v1][v2] = MaxWeight;
	G->numOfEdges--;
}

//在图G中寻找序号为v的顶点的第一个邻接顶点
//如果这样的顶点存在，则返回该邻接顶点的序号，否则返回-1
int GetFirstVex(AdjMGraph G, int v) {
	int col;
	if (v < 0 || v >= G.Vertices.size) {
		printf("参数v1越界出错!\n");
		exit(1);
	}
	for (col = 0; col < G.Vertices.size; col++)
		if (G.edge[v][col] > 0 && G.edge[v][col] < MaxWeight)
			return col;
	return -1;
}

int GetNextVex(AdjMGraph G, int v1, int v2) {
	//在图中寻找V1顶点的邻接顶点V2的下一个邻接顶点
	//如果这样的邻接顶点存在，则返回该邻接顶点的序号，否则返回-1
	int col;
	if (v1 < 0 || v1 > G.Vertices.size || v2 < 0 || v2 > G.Vertices.size)
	{
		printf("参数v1或v2越界出错!\n");
		exit(1);
	}
	for (col = v2 + 1; col <= G.Vertices.size; col++)
		if (G.edge[v1][col] > 0 && G.edge[v1][col] < MaxWeight)
			return col;
	return -1;
}

/*在图G中插入n个顶点信息V和e条边信息E*/
void CreatGraph(AdjMGraph* G, DataType V[], int n,
	RowColWeight E[], int e) {
	int i, k;
	Initiate(G, n);		       	/*顶点顺序表初始化*/
	for (i = 0; i < n; i++)
		InsertVertex(G, V[i]);	/*顶点插入*/
	for (k = 0; k < e; k++)
		InsertEdge(G, E[k].row, E[k].col, E[k].weight);/*边插入*/
}

//int main(void) {
//	AdjMGraph g1;
//	DataType a[] = { 'A','B','C','D','E' };
//	RowColWeight rcw[] =
//	{ {0,1,10},{0,4,20},{1,3,30},{2,1,40},{3,2,50} };
//	int n = 5, e = 5;
//	int i, j;
//	CreatGraph(&g1, a, n, rcw, e);
//	DeleteEdge(&g1, 0, 4);
//	printf("顶点集合为：");
//	for (i = 0; i < g1.Vertices.size; i++)
//		printf("%c   ", g1.Vertices.list[i]);
//	printf("\n");
//	printf("权值集合为：\n");
//	for (i = 0; i < g1.Vertices.size; i++) {
//		for (j = 0; j < g1.Vertices.size; j++)
//			printf("%5d   ", g1.edge[i][j]);
//		printf("\n");
//	}
//}
