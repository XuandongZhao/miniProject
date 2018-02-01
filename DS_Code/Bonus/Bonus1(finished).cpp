/*������ �������7�� 3150104910 
��������Ҫ�õ���������ȵ��㷨
������������ÿ��·��������������*/
#include<stdio.h>
#include<stdlib.h>//ͷ�ļ�����
#define MAX 100 //�����������

void DFS(int root, int sum); //DFS��������
void Print(int next); //��ӡ��������

/*���岻ͬ�Ĵ�������*/
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
	scanf("%d%d%d", &N, &R, &sum);//��ʼ���� 
	for (i = 0; i < N; i++)
		scanf("%d", &Weight[i]);//����Ȩ�� 
	if(R == 0)//ֻ����һ��������� 
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
/*��ÿһ������Ȩ���Ƚ����������������Ҫ��*/
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
/*���������������*/ 
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
/*��ӡ����*/ 
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
