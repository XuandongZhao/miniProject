#include<stdio.h> 
#include<stdlib.h>
#define MAXNUMBER 100

int weight[MAXNUMBER] = { 0 };
int parent[MAXNUMBER] = { 0 };
int childNum[MAXNUMBER] = { 0 };
int Sum[MAXNUMBER] = { 0 };
int linkNode[MAXNUMBER][MAXNUMBER] = { 0 };
void DFS(int cur, int s);
void print(int next);

int main()
{
	int N, R, sum;
	freopen("in.txt","r",stdin); 
	scanf("%d%d%d", &N, &R, &sum);
	int i,j,k,m,temp;
	for (i = 0; i < N; i++)
	{
		scanf("%d", &weight[i]);
	}
	int nonleaf, num, leaf;
	for (i = 0; i < R; i++)
	{
		scanf("%d %d", &nonleaf, &num);
		childNum[nonleaf] = num;
		for (j = 0; j < num; j++)
		{
			scanf("%d", &leaf);
			linkNode[nonleaf][j] = leaf;
			parent[leaf] = nonleaf;
		}
		for (k = 0; k < num - 1; k++)
		{
			for (m = 0; m < num - 1 - k; m++)
			{
				if (weight[linkNode[nonleaf][m]] < weight[linkNode[nonleaf][m + 1]])
				{
					temp = linkNode[nonleaf][m];
					linkNode[nonleaf][m] = linkNode[nonleaf][m + 1];
					linkNode[nonleaf][m + 1] = temp;
				}
			}
		}
	}
	if (R == 0)
	{
		if (sum == weight[0])
			printf("%d", weight[0]);
		return 0;
	}
	for (i = 0; weight[i]; i++)
	{
		Sum[i] = weight[i];
	}
	DFS(0, sum);
	return 0;
}

void DFS(int cur, int s)
{
	int next,i;
	for (i = 0; i < childNum[cur]; i++)
	{
		next = linkNode[cur][i];
		Sum[next] = Sum[cur] + weight[next];
		if (Sum[next] == s)
		{
			if (childNum[next] == 0)
			{
				print(next);
				printf("\n");
			}
			else
			{
				continue;
			}
		}
		else if (Sum[next] < s)
		{
			DFS(next, s);
		}
		else
		{
			continue;
		}
	}
}

void print(int next)
{
	int result[MAXNUMBER];
	int i=0;
	while (next != 0)
	{
		result[i++] = weight[next];
		next = parent[next];
	}
	result[i] = weight[0]; 
	for (; i >0; i--)
	{
		printf("%d ", result[i]);
	}
	printf("%d",result[0]);
}
