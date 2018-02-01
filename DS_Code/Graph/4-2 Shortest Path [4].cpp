#include <stdio.h>
#include <stdlib.h>

//typedef enum { false, true } bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist(MGraph Graph, int dist[], int path[], Vertex S);

int main()
{
	int dist[MaxVertexNum], path[MaxVertexNum];
	Vertex S, V;
	MGraph G = ReadG();

	scanf("%d", &S);
	ShortestDist(G, dist, path, S);

	for (V = 0; V<G->Nv; V++)
		printf("%d ", dist[V]);
	printf("\n");
	for (V = 0; V<G->Nv; V++)
		printf("%d ", path[V]);
	printf("\n");

	return 0;
}
MGraph ReadG()
{
	int i, V, M, Weight;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode));
	scanf("%d%d", &(Graph->Nv), &(Graph->Ne));
	for (V = 0; V<MaxVertexNum; V++)
		for (M = 0; M<MaxVertexNum; M++)
			Graph->G[V][M] = INFINITY;
	for (i = 0; i < Graph->Ne; i++)
	{
		scanf("%d%d%d", &V, &M, &Weight);
		Graph->G[V][M] = Weight;
	}
	return Graph;
}

void ShortestDist(MGraph Graph, int dist[], int path[], Vertex S)
{
	int findmin(MGraph Graph, int collected[], int dist[]);
	int i, V, M;
	int collected[MaxVertexNum] = { 0 };
	for (V = 0; V < Graph->Nv; V++)
	{

		dist[V] = Graph->G[S][V];
		if (Graph->G[S][V] < INFINITY)
		{
			path[V] = S;
		}
		else
			path[V] = -1;
	}
	collected[S] = 1;
	dist[S] = 0;
	path[S] = -1;
	while (1)
	{
		V = findmin(Graph, collected, dist);
		if (V == -1)
			break;
		collected[V] = 1;
		for (M = 0; M < Graph->Nv; M++)
		{
			if (collected[M] == 0 && dist[M] > dist[V] + Graph->G[V][M] )
			{
				dist[M] = dist[V] + Graph->G[V][M];
				path[M] = V;
			}
		}
	}
	for (i = 0; i<Graph->Nv; i++)
	{
		if (dist[i] == INFINITY)
			dist[i] = -1;
	}
}
int findmin(MGraph Graph, int collected[], int dist[])
{
	int V, M, Min;
	int MinDist = INFINITY;
	for (V = 0; V < Graph->Nv; V++)
	{
		if (collected[V] == 0 && dist[V] < MinDist)
		{
			MinDist = dist[V];
			Min = V;
		}
	}
	if (MinDist == INFINITY)
		return -1;
	else
		return Min;
}