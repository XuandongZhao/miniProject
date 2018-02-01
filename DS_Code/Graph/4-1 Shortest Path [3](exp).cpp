#include <stdio.h>
#include <stdlib.h>




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


MGraph ReadG()
{
	MGraph P;
	int i, j, k;
	P = (MGraph)malloc(sizeof(struct GNode));
	scanf("%d%d", &P->Nv, &P->Ne);
	for (j = 0; j<MaxVertexNum; j++) {
		for (k = 0; k<MaxVertexNum; k++) {
			P->G[j][k] = -1;
		}
	}
	for (i = 0; i<P->Ne; i++) {
		int m, n;
		scanf("%d%d", &m, &n);
		scanf("%d", &P->G[m][n]);
	}

	return P;
}




/* Your function will be put here */
void ShortestDist(MGraph Graph, int dist[], int count[], Vertex S)
{
	int findmin(MGraph graph, int d[], int know[]);
	int i;
	Vertex known[MaxVertexNum];
	Vertex V, W;
	for (i = 0; i<Graph->Nv; i++) {
		dist[i] = INFINITY;
		count[i] = 0;
		known[i] = -1;
	}
	count[S] = 1;
	dist[S] = 0;
	for (;;) {
		V = findmin(Graph, dist, known);
		if (V == -1)
			break;
		known[V] = 1;
		for (W = 0; W<Graph->Nv; W++) {
			if (Graph->G[V][W]>0) {
				if (dist[V] + Graph->G[V][W]<dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W];
					count[W] = count[V];
				}
				else if (dist[V] + Graph->G[V][W] == dist[W])
					count[W] = count[W] + count[V];


			}
		}
	}
	for (i = 0; i<Graph->Nv; i++) {
		if (dist[i] == INFINITY) {
			dist[i] = -1;
			count[i] = 0;
		}
	}
}
int findmin(MGraph graph, int d[], int know[])
{
	int i;
	int count = 0;
	int min;
	for (min = 0; min<graph->Nv; min++) {
		if (know[min] == -1)
			break;
	}
	for (i = 0; i<graph->Nv; i++) {
		if (d[min]>d[i] && know[i] == -1)
			min = i;
		if (know[i] == 1)
			count++;
	}
	if (count != graph->Nv)
		return min;
	else return -1;
}