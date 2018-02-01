#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX 2500
struct Edge {
	int City1;
	int City2;
	int Cost;
	int Status;
};
int comp1(const void *a, const void *b);
int comp2(const void *a, const void *b);
int kruskal(struct Edge* Road, int City, int N, int M);
int Find(int *Set, int x);
int main()
{
	int N, M;
	int i, j;
	int *Citycost, *Temp;
	int flag = 1;
	//Edge *Road = NULL;
	scanf("%d%d", &N, &M);
	struct Edge Road[MAX];
	//Road = (Edge*)malloc(sizeof(Edge)*(M + 2));
	Citycost = (int*)malloc(sizeof(int)*(N + 1));
	Temp = (int*)malloc(sizeof(int)*(N + 1));
	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d%d", &Road[i].City1, &Road[i].City2, &Road[i].Cost, &Road[i].Status);
		if (Road[i].Status == 1)
			Road[i].Cost = 0;
	}
	qsort(Road, M, sizeof(Road[0]), comp1);
	memset(Citycost, 0, sizeof(int) * (N + 2));
	memset(Temp, 0, sizeof(int)*(N + 2));
	for (i = 1; i <= N; i++)
	{
		Citycost[i] = kruskal(Road, i, N, M);
		Temp[i] = Citycost[i];
	}
	qsort(Citycost, M, sizeof(int), comp2);

	if (Citycost[0] == 0)
		printf("0");
	else
	{
		for (j = 1; j <= N; j++)
		{
			if (Temp[j] == Citycost[0])
			{
				if (flag)
				{
					printf("%d", j);
					flag = 0;
				}
				else
					printf(" %d", j);
			}
		}
	}
	return 0;
}
int kruskal(struct Edge* Road, int City, int N, int M)
{
	int Value = 0, i;
	int Root1, Root2;
	int count = 0;
	int Set[200];
	//Value = 0;
	//Set = (int*)malloc(sizeof(int)*(N + 1));
	//memset(Set, -1, sizeof(int) * (N + 1));
	for (i = 0; i < N + 5; i++)
	{
		Set[i] = -1;
	}
	for (i = 0; i < M; i++)
	{
		if (Road[i].City1 == City || Road[i].City2 == City)
			continue;
		Root1 = Find(Set, Road[i].City1);
		Root2 = Find(Set, Road[i].City2);
		if (Root1 == Root2)
			continue;
		else
		{
			if (Set[Root2] < Set[Root1])
			{ /* 如果集合2比较大 */
				Set[Root2] += Set[Root1];     /* 集合1并入集合2  */
				Set[Root1] = Root2;
				count++;
			}
			else
			{                         /* 如果集合1比较大 */
				Set[Root1] += Set[Root2];     /* 集合2并入集合1  */
				Set[Root2] = Root1;
				count++;
			}
		}
		Value += Road[i].Cost;
	}
	if (count != N - 2)
		return 0x7FFFFFFF;
	else
		return Value;
}
int Find(int *Set, int x)
{
	if (Set[x] < 0)
		return x;
	else
		return(Set, Set[x]);
}
int comp1(const void *a, const void *b)
{
	return (*(struct Edge*)b).Cost < (*(struct Edge*)a).Cost ? 1 : -1;
}
int comp2(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;
}