/*
������ �������7�� 3150104910 Num:02
��������Ҫ����Kruskal�㷨����С����������ϼ�֦�����š�·��ѹ��������⡣
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
};/*���ߴ洢*/
int comp1(const void *a, const void *b);/*Qsort�ȽϺ���1*/

int comp2(const void *a, const void *b);/*Qsort�ȽϺ���2*/

int kruskal(struct Edge* Road, int City, int N, int M);
/*Kruskal����������ÿ�����е�Cost����Ҫ�̶ȣ� ����С������*/

int Find(int *Set, int x);/*���鼯�е�·��ѹ��*/

int main()
{
	int N, M;/*����������·��*/
	int i, j;/*�������*/
	int *Citycost, *Temp;/*ÿ�����е�Cost*,��Temp���鸴��Citycost,����֮������*/
	int flag = 1;/*���ʱ�ı���*/

	scanf("%d%d", &N, &M);
	struct Edge Road[MAX];
	Citycost = (int*)malloc(sizeof(int)*(N + 1));
	Temp = (int*)malloc(sizeof(int)*(N + 1));/*�����ʼ������*/

	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d%d", &Road[i].City1, &Road[i].City2, &Road[i].Cost, &Road[i].Status);
		if (Road[i].Status == 1)
			Road[i].Cost = 0;/*�����·�Ǻõģ�����Ϊ������Ҫ�̶�Ϊ0*/
	}/*Road�����ʼ��*/

	qsort(Road, M, sizeof(Road[0]), comp1);/*�����е�·����Ҫ�̶�����*/
	memset(Citycost, 0, sizeof(int) * (N + 2));
	memset(Temp, 0, sizeof(int)*(N + 2));/*�������*/
	for (i = 1; i <= N; i++)
	{
		Citycost[i] = kruskal(Road, i, N, M);
		Temp[i] = Citycost[i];
	}/*����Kruskal����������������*/

	qsort(Citycost, N + 1, sizeof(int), comp2);/*�Գ�����Ҫ�̶�����*/
	if (Citycost[0] == 0)
		printf("0");/*���ȫ����ͨ����Ҫ�̶�Ϊ0*/
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
	}/*������*/
	return 0;
}
int kruskal(struct Edge* Road, int City, int N, int M)
{
	int i;
	int Root1, Root2;
	int count = 0, Value = 0;
	int Set[1000];/*������ʼ��*/

	for (i = 1; i <= N; i++)
	{
		Set[i] = -1;
	}/*���鼯��ʼ��*/
	for (i = 0; i < M; i++)
	{
		if (count == N - 2)
			break;/*��֦����������Ѿ��������г��У�����ѭ���������㷨ʱ��*/
		if (Road[i].City1 == City || Road[i].City2 == City)
			continue;/*������ǰ����ĳ���*/
		Root1 = Find(Set, Road[i].City1);
		Root2 = Find(Set, Road[i].City2);/*���Ҹ��ڵ�*/
		if (Root1 == Root2)
			continue;/*�������ͬһ������*/
		else
		{
			if (Set[Root2] < Set[Root1])
			{ /* �������2�Ƚϴ� */
				Set[Root2] += Set[Root1];/* ����1���뼯��2*/
				Set[Root1] = Root2;
				count++;
			}
			else
			{ /* �������1�Ƚϴ� */
				Set[Root1] += Set[Root2];/* ����2���뼯��1*/
				Set[Root2] = Root1;
				count++;
			}
		}
		Value += Road[i].Cost;/*��·���Ļ��Ѽ����ܻ���*/
	}
	if (count != N - 2)
		return 0x7FFFFFFF;/*����޷���ͨ���򷵻�����ֵ*/
	else
		return Value;/*���ػ���*/
}

int Find(int *Set, int x)
{
	if (Set[x] < 0)
		return x;
	else
		return Set[x] = Find(Set, Set[x]);/*·��ѹ��*/
}
/*Qsort�ȽϺ���1*/
int comp1(const void *a, const void *b)
{
	return (*(struct Edge*)b).Cost < (*(struct Edge*)a).Cost ? 1 : -1;/*��С����*/
}
/*Qsort�ȽϺ���2*/
int comp2(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;/*�Ӵ�С*/
}

