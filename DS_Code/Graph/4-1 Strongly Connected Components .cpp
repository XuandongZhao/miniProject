#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
	Vertex Vert;
	PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
	int NumOfVertices;
	int NumOfEdges;
	PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV(Vertex V)
{
	printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V));

int main()
{
	Graph G = ReadG();
	StronglyConnectedComponents(G, PrintV);
	return 0;
}

/* Your function will be put here */
Graph ReadG()
{
	Graph G;
	PtrToVNode P;
	int i, j;
	int V, M;

	G = (Graph)malloc(sizeof(GNode));
	
	scanf("%d%d", &G->NumOfVertices, &G->NumOfEdges);
	for (i = 0; i < G->NumOfEdges; i++)
	{
		scanf("%d%d", &V, &M);
		P = (PtrToVNode)malloc(sizeof(VNode));
		P->Vert = M;
		P->Next = NULL;
		G->Array[V]->Next = P;
	}
	return G;
}
int DFN[MaxVertices];
int Low[MaxVertices];

void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V))
{
	for (int i = 0; i < G->NumOfVertices; i++)
	{
		DFN[i] = Low[i] = 0;
	}
	for (i = 0; i < G->NumOfVertices; i++)
	{
		Tarjan(int i)
	}
}