/*
赵宣栋 周六班第7组 3150104910 Num:02
本程序主要运用Kruskal算法求最小生成树，配合剪枝、快排、路径压缩求解问题。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX 250000

struct Edge {
	int City1;
	int City2;
	int Cost;
	int Status;
};/*按边存储*/
int comp1(const void *a, const void *b);/*Qsort比较函数1*/

int comp2(const void *a, const void *b);/*Qsort比较函数2*/

int kruskal(struct Edge* Road, int City, int N, int M);
/*Kruskal函数，计算每个城市的Cost（重要程度） 求最小生成树*/

int Find(int *Set, int x);/*并查集中的路径压缩*/

int main()
{
	int N, M;/*城市数及道路数*/
	int i, j;/*计算变量*/
	int *Citycost, *Temp;/*每个城市的Cost*,用Temp数组复制Citycost,便于之后的输出*/
	int flag = 1;/*输出时的变量*/

	scanf("%d%d", &N, &M);
	struct Edge Road[MAX];
	Citycost = (int*)malloc(sizeof(int)*(N + 1));
	Temp = (int*)malloc(sizeof(int)*(N + 1));/*数组初始化操作*/

	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d%d", &Road[i].City1, &Road[i].City2, &Road[i].Cost, &Road[i].Status);
		if (Road[i].Status == 1)
			Road[i].Cost = 0;/*如果道路是好的，就认为它的重要程度为0*/
	}/*Road数组初始化*/

	qsort(Road, M, sizeof(Road[0]), comp1);/*将所有道路的重要程度排序*/
	memset(Citycost, 0, sizeof(int) * (N + 2));
	memset(Temp, 0, sizeof(int)*(N + 2));/*清零操作*/
	for (i = 1; i <= N; i++)
	{
		Citycost[i] = kruskal(Road, i, N, M);
		Temp[i] = Citycost[i];
	}/*调用Kruskal函数，并复制数组*/

	qsort(Citycost, N + 1, sizeof(int), comp2);/*对城市重要程度排序*/
	if (Citycost[0] == 0)
		printf("0");/*如果全部连通，重要程度为0*/
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
	}/*结果输出*/
	return 0;
}
int kruskal(struct Edge* Road, int City, int N, int M)
{
	int i;
	int Root1, Root2;
	int count = 0, Value = 0;
	int Set[1000];/*变量初始化*/

	for (i = 1; i <= N; i++)
	{
		Set[i] = -1;
	}/*并查集初始化*/
	for (i = 0; i < M; i++)
	{
		if (count == N - 2)
			break;/*剪枝操作，如果已经遍历所有城市，跳出循环，控制算法时间*/
		if (Road[i].City1 == City || Road[i].City2 == City)
			continue;/*跳过当前计算的城市*/
		Root1 = Find(Set, Road[i].City1);
		Root2 = Find(Set, Road[i].City2);/*查找根节点*/
		if (Root1 == Root2)
			continue;/*如果属于同一个集合*/
		else
		{
			if (Set[Root2] < Set[Root1])
			{ /* 如果集合2比较大 */
				Set[Root2] += Set[Root1];/* 集合1并入集合2*/
				Set[Root1] = Root2;
				count++;
			}
			else
			{ /* 如果集合1比较大 */
				Set[Root1] += Set[Root2];/* 集合2并入集合1*/
				Set[Root2] = Root1;
				count++;
			}
		}
		Value += Road[i].Cost;/*将路径的花费计入总花费*/
	}
	if (count != N - 2)
		return 0x7FFFFFFF;/*如果无法连通，则返回无限值*/
	else
		return Value;/*返回花费*/
}

int Find(int *Set, int x)
{
	if (Set[x] < 0)
		return x;
	else
		return Set[x] = Find(Set, Set[x]);/*路径压缩*/
}
/*Qsort比较函数1*/
int comp1(const void *a, const void *b)
{
	return (*(struct Edge*)b).Cost < (*(struct Edge*)a).Cost ? 1 : -1;/*从小到大*/
}
/*Qsort比较函数2*/
int comp2(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;/*从大到小*/
}

