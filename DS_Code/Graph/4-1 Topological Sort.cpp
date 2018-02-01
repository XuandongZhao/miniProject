#include <stdio.h>
#include <stdlib.h>

//typedef enum {true,false} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;
	PtrToAdjVNode Next;
};

typedef struct Vnode {
	PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool TopSort(LGraph Graph, Vertex TopOrder[]);

int main()
{
	int i;
	Vertex TopOrder[MaxVertexNum];
	LGraph G = ReadG();

	if (TopSort(G, TopOrder) == true)
		for (i = 0; i<G->Nv; i++)
			printf("%d ", TopOrder[i]);
	else
		printf("ERROR");
	printf("\n");

	return 0;
}
LGraph ReadG()
{
	LGraph Graph;
	PtrToAdjVNode NewNode[MaxVertexNum];
	Vertex V, V1, V2;
	int  i;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	scanf("%d", &(Graph->Nv));

	for (V = 0; V < Graph->Nv; V++)
	{
		Graph->G[V].FirstEdge = NULL;
	}

	scanf("%d", &(Graph->Ne));   /* 读入边数 */
	for (i = 0; i < Graph->Ne; i++)
	{
		scanf("%d %d", &V1, &V2);
		NewNode[i] = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		NewNode[i]->AdjV = V2;
		NewNode[i]->Next = Graph->G[V1].FirstEdge;
		Graph->G[V1].FirstEdge = NewNode[i];
	}
	return Graph;
}

bool TopSort(LGraph Graph, Vertex TopOrder[])
{
	int counter, i, j, front, rear;
	front = rear = counter = 0;
	int a[MaxVertexNum] = { 0 };
	int Q[MaxVertexNum] = { 0 };
	PtrToAdjVNode P, node;

	for (i = 0; i < Graph->Nv; i++)
	{
		for (P = Graph->G[i].FirstEdge; P != NULL; P = P->Next)
			a[P->AdjV]++;
	}

	for (i = 0; i < Graph->Nv; i++)
	{
		if (a[i] == 0)
			Q[rear++] = i;
	}

	while (front != rear)
	{
		j = Q[front++];
		TopOrder[counter++] = j;
		for (node = Graph->G[j].FirstEdge; node != NULL; node = node->Next)
		{
			a[node->AdjV]--;
			if (a[node->AdjV] == 0)
			{
				Q[rear++] = node->AdjV;
			}
		}
	}
	if (counter != Graph->Nv)
		return false;
	return true;
}
