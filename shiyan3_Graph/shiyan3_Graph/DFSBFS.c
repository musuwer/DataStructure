#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef char DataType;
#define MaxSize 100  //
#define MaxVertices 10 //
#define MaxEdges 100 //
#define MaxWeight 7FFFH
#define MaxQueueSize 100
#include "SeqCQueue.h"
#include "AdjMGraph.c"
//#include "AdjMGraphCreate.h"
//#include "AdjMGraphTraverse.h"

void Visit(DataType item) {
	printf("%c   ", item);
}

void DepthFSearch(AdjMGraph G, int v, int visited[],
	void (*Visit)(DataType item)) {
	int w;
	Visit(G.Vertices.list[v]);
	visited[v] = 1;
	w = GetFirstVex(G, v);						while (w != -1) {
		//递归访问以w为起点的图
		if (!visited[w])
			DepthFSearch(G, w, visited, Visit);
		w = GetNextVex(G, v, w);
	}
}

void BroadFSearch(AdjMGraph G, int v, int visited[],
	void Visit(DataType item)) {
	DataType u, w;
	SeqCQueue queue;
	Visit(G.Vertices.list[v]);	//1
	visited[v] = 1;			//1		 
	QueueInitiate(&queue);	//2
	QueueAppend(&queue, v);	//2					
	while(QueueNotEmpty(queue)) { 
		QueueDelete(&queue, &u);	//(1)
		w = GetFirstVex(G, u);	//(2)
		while (w != -1) {		//(3) 		
			if (!visited[w]) {
				Visit(G.Vertices.list[w]);
				visited[w] = 1;							QueueAppend(&queue, w);
			}
			w = GetNextVex(G, u, w);
		}
	}
}
void DepthFirstSearch(AdjMGraph G, void Visit(DataType item)) {
	int i;
	int* visited = (int*)malloc(sizeof(int) * G.Vertices.size);
	for (i = 0; i < G.Vertices.size; i++)
		visited[i] = 0;

	for (i = 0; i < G.Vertices.size; i++)
		if (!visited[i])
			DepthFSearch(G, i, visited, Visit);
	free(visited);
}
void BroadFirstSearch(AdjMGraph G, void Visit(DataType item)) {
	int i;
	int* visited = (int*)malloc(sizeof(int) * G.Vertices.size);

	for (i = 0; i < G.Vertices.size; i++)
		visited[i] = 0;

	for (i = 0; i < G.Vertices.size; i++)
		if (!visited[i])
			BroadFSearch(G, i, visited, Visit);

	free(visited);
}
void main(void) {
	AdjMGraph g1;
	DataType a[] = { 'A','B','C','D','E' };
	RowColWeight rcw[] = { {0,1,10},{0,4,20},{1,3,30}, {2,1,40},{3,2,50} };
	int n = 5, e = 5;
	CreatGraph(&g1, a, n, rcw, e);
	printf("深度优先搜索序列为：");
	DepthFirstSearch(g1, Visit);
	printf("\n广度优先搜索序列为：");
	BroadFirstSearch(g1, Visit);
}