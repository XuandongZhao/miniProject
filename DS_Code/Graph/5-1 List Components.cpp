/*写的太垃圾了。。。。。。*/
#include<stdio.h>
#include<stdlib.h>
#define MAX 200

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
	int AdjV;        /* 邻接点下标 */
	PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;/* 边表头指针 */
	int Data;            /* 存顶点的数据 */
						 /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MAX];    /* AdjList是邻接表类型 */

				   /* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;     /* 顶点数 */
	int Ne;     /* 边数   */
	AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */;

void BFS(LGraph Graph, int i, int visit[]);
void DFS(LGraph Graph, int i, int visit[]);
int main()
{
	int i,j,k, M, N, V,temp;
	int x, y;
	LGraph Graph;
	PtrToAdjVNode P1, P2;
	Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	scanf("%d%d", &Graph->Nv, &Graph->Ne);
	int visit1[MAX] = { 0 };
	int visit2[MAX] = { 0 };
	int A[MAX][MAX];
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			A[MAX][MAX] = -1;
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	for (i = 0; i < Graph->Ne; i++)
	{
		scanf("%d%d", x, y);
		A[x][i] = y;
		A[y][i] = x;
	}
	for (k = 0; k < Graph->Nv + 1; k++)
	{
		for (i = 0; i < MAX - 1; i++)
		{
				for (j = 0; j < MAX - 1 - i; j++)
				{
					if (A[k][j] < A[k][j + 1])
					{
						temp = A[k][j + 1];
						A[k][j + 1] = A[k][j];
						A[k][j] = temp;
					}
				}
		}
	}
	for (i = 0; i < Graph->Nv; i++)
	{
		for (j = 0; A[i][j] != -1; j++)
		{
			P1 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
			P1->AdjV = A[i][j];
			P1->Next = Graph->G[i].FirstEdge;
		}
	}
	/*for (i = 0; i < Graph->Ne; i++)
	{
		scanf("%d%d", &M, &N);
		P1 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		P1->AdjV = N;
		P1->Next = Graph->G[M].FirstEdge;
		Graph->G[M].FirstEdge = P1;
		P2 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		P2->AdjV = M;
		P2->Next = Graph->G[N].FirstEdge;
		Graph->G[N].FirstEdge = P2;
	}*/

	for (i = 0; i < Graph->Nv; i++)
	{
		if (visit1[i] == 0)
		{
			printf("{ ");
			DFS(Graph, i, visit1);
			printf("}\n");
		}
	}

	for (i = 0; i < Graph->Nv; i++)
	{
		if (visit2[i] == 0)
		{
			printf("{ ");
			BFS(Graph, i, visit2);
			printf("}\n");
		}
	}
	return 0;
}

void DFS(LGraph Graph, int i, int visit[])
{
	PtrToAdjVNode P;
	visit[i] = 1;
	printf("%d ", i);
	for (P = Graph->G[i].FirstEdge; P; P = P->Next)
	{
		if (visit[P->AdjV] == 0)
			DFS(Graph, P->AdjV, visit);
	}
}

void BFS(LGraph Graph, int i, int visit[])
{
	PtrToAdjVNode AddQ(PtrToAdjVNode Q, PtrToAdjVNode S);
	int DeleteQ(PtrToAdjVNode Q);
	int IsEmpty(PtrToAdjVNode Q);

	int V;
	PtrToAdjVNode Q, P, S;
	Q = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	Q->Next = NULL;
	S = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	S->Next = NULL;
	S->AdjV = i;
	visit[i] = 1;
	printf("%d ", i);

	AddQ(Q, S);
	while (!IsEmpty(Q))
	{
		V = DeleteQ(Q);
		for (P = Graph->G[V].FirstEdge; P; P = P->Next)
		{
			if (visit[P->AdjV] == 0)
			{
				printf("%d ", P->AdjV);
				visit[P->AdjV] = 1;
				//if(!IsEmpty(Q))
				AddQ(Q, P);
			}
		}
	}
	return;
}

PtrToAdjVNode AddQ(PtrToAdjVNode Q, PtrToAdjVNode S)
{
	PtrToAdjVNode Temp;
	Temp = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	Temp->AdjV = S->AdjV;
	Temp->Next = Q->Next;
	Q->Next = Temp;
	return Q;
}
int IsEmpty(PtrToAdjVNode Q)
{
	if (Q->Next == NULL)
		return 1;
	else
		return 0;
}
int DeleteQ(PtrToAdjVNode Q)
{
	PtrToAdjVNode Temp;
	int i;

	Temp = Q->Next;
	Q->Next = Temp->Next;
	Temp->Next = NULL;
	i = Temp->AdjV;
	free(Temp);
	return i;
}