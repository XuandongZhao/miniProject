/*赵宣栋 周六班第7组 3150104910 
本程序主要用到了深度优先的算法
将符合条件的每条路径进行排序后输出*/
#include<stdio.h>
#include<stdlib.h>//头文件声明
#define MAX 100 //定义最大数量

void DFS(int root, int sum); //DFS函数声明
void Print(int next); //打印函数声明

/*定义不同的处理数组*/
int Child[MAX] = {0};
int Parent[MAX] = {0};
int Link[MAX][MAX] = {0};
int Weight[MAX] = {0};
int Sum[MAX] = {0};

int main()
{
	int N, R, sum;
	int i, j, k, m,temp;
	int root, leaf,num;
	scanf("%d%d%d", &N, &R, &sum);//初始输入 
	for (i = 0; i < N; i++)
		scanf("%d", &Weight[i]);//输入权重 
	if(R == 0)//只输入一个结点的情况 
	{
		if(Weight[0] == sum)
			printf("%d",sum);
		return 0;
	}
	for (i = 0; i < R; i++)
	{
		scanf("%d%d", &root, &num);
		Child[root] = num;
		for (j = 0; j < num; j++)
		{
			scanf("%d", &leaf);
			Link[root][j] = leaf;
			Parent[leaf] = root;
		}
/*将每一个结点的权重先进行排序，以满足输出要求*/
		for (k = 0; k < num-1; k++)
			for (m = 0; m < num - k - 1; m++)
				if (Weight[Link[root][m]] < Weight[Link[root][m + 1]]) 
				{
					temp = Link[root][m];
					Link[root][m] = Link[root][m + 1];
					Link[root][m + 1] = temp;
				}
	}
	for (i = 0; Weight[i]; i++)
		Sum[i] = Weight[i];
	DFS(0, sum);
	return 0;
}
/*深度优先搜索函数*/ 
void DFS(int root, int sum)
{
	int next, i;
	for (i = 0; i < Child[root]; i++)
	{
		next = Link[root][i];
		Sum[next] = Sum[root] + Weight[next];
		if (Sum[next] == sum)
		{
			if (Child[next] == 0)
			{
				Print(next);
				printf("\n");
			}
			else
				continue;
		}
		else if (Sum[next] < sum)
			DFS(next, sum);
		else
			continue;
	}
}
/*打印函数*/ 
void Print(int next)
{
	int i=0;
	int result[MAX];
	while (next != 0)
	{
		result[i++] = Weight[next];
		next = Parent[next];
	}
	result[i] = Weight[0];
	for (; i > 0; i--)
		printf("%d ", result[i]);
	printf("%d", result[0]);
}
