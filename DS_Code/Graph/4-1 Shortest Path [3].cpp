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

void ShortestDist(MGraph Graph, int dist[], int count[], Vertex S);

int main()
{
	int dist[MaxVertexNum], count[MaxVertexNum];
	Vertex S, V;
	MGraph G = ReadG();

	scanf("%d", &S);
	ShortestDist(G, dist, count, S);

	for (V = 0; V<G->Nv; V++)
		printf("%d ", dist[V]);
	printf("\n");
	for (V = 0; V<G->Nv; V++)
		printf("%d ", count[V]);
	printf("\n");

	return 0;
}

/* Your function will be put here */
MGraph ReadG()
{
	MGraph Graph;
	Vertex V, W, V1, V2;
	int  i, Nv, Weight;

	scanf("%d", &Nv);
	Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = Nv;
	Graph->Ne = 0;
	for (V = 0; V<MaxVertexNum; V++)
		for (W = 0; W<MaxVertexNum; W++)
			Graph->G[V][W] = INFINITY;
	scanf("%d", &(Graph->Ne));

	if (Graph->Ne != 0)
	{
		for (i = 0; i<Graph->Ne; i++)
		{
			scanf("%d%d%d", &V1, &V2, &Weight);
			Graph->G[V1][V2] = Weight;
		}
	}
	return Graph;
}

Vertex FindMinDist(MGraph Graph, int dist[], int collected[]);
void ShortestDist(MGraph Graph, int dist[], int count[], Vertex S)
{
	int i, j, k, V, W;
	int collected[MaxVertexNum];

	for (V = 0; V<Graph->Nv; V++)
	{
		dist[V] = Graph->G[S][V];
		if (dist[V]<INFINITY)
			count[V] = 1;
		else
			count[V] = 0;
		collected[V] = 0;
	}
	dist[S] = 0;
	count[S] = 1;
	collected[S] = 1;
	while (1)
	{
		/* V = 未被收录顶点中dist最小者 */
		V = FindMinDist(Graph, dist, collected);
		if (V == -1) /* 若这样的V不存在 */
			break;      /* 算法结束 */
		collected[V] = 1;  /* 收录V */
		for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
		{							    /* 若W是V的邻接点并且未被收录 */
			if (collected[W] == 0 && Graph->G[V][W] < INFINITY)
			{
				/* 若收录V使得dist[W]变小 */
				if (dist[V] + Graph->G[V][W] < dist[W])
				{
					dist[W] = dist[V] + Graph->G[V][W]; /* 更新dist[W] */
					count[W] = count[V]; /* 更新S到W的路径 */
				}
				else if (dist[V] + Graph->G[V][W] == dist[W])
				{
					count[W] = count[W] + count[V];
				}
			}
		}
	} /* while结束*/
	for (i = 0; i<Graph->Nv; i++)
	{
		if (dist[i] == INFINITY)
			dist[i] = -1;
	}
}

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++)
	{
		if (collected[V] == 0 && dist[V]<MinDist)
		{
			/* 若V未被收录，且dist[V]更小 */
			MinDist = dist[V]; /* 更新最小距离 */
			MinV = V; /* 更新对应顶点 */
		}
	}
	if (MinDist < INFINITY) /* 若找到最小dist */
		return MinV; /* 返回对应的顶点下标 */
	else return -1;  /* 若这样的顶点不存在，返回错误标记 */
}
