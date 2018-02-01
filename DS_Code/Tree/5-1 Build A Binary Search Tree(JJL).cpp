#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
	int Key;
	int Left;
	int Right;
};

void inOrderTraverse(int i);
int cmp(const void *a, const void *b);
Tree Forests;
int *num;
int j;

int main(void)
{
	int i, TotalNodes;
	scanf("%d", &TotalNodes);
	Forests = (Tree)malloc(sizeof(struct TreeNode)*TotalNodes);
	num = (int*)malloc(sizeof(int)*TotalNodes);
	j = 0;
	int temp[TotalNodes], front, rear;
	front = 0; rear = 1;
	temp[0] = 0;

	for (i = 0; i<TotalNodes; i++)
	{
		scanf("%d%d", &Forests[i].Left, &Forests[i].Right);
	}

	for (i = 0; i<TotalNodes; i++)
	{
		scanf("%d", &num[i]);
	}
	qsort(num, TotalNodes, sizeof(num[0]), cmp);

	inOrderTraverse(0);

	while (front != rear)
	{

		printf("%d", Forests[temp[front]].Key);

		if (front < TotalNodes - 1) printf(" ");
		if (Forests[temp[front]].Left >= 0)
		{
			temp[rear++] = Forests[temp[front]].Left;
		}
		if (Forests[temp[front]].Right >= 0)
		{
			temp[rear++] = Forests[temp[front]].Right;
		}
		front++;
	}
}

void inOrderTraverse(int i)
{
	if (i >= 0)
	{
		inOrderTraverse(Forests[i].Left);
		Forests[i].Key = num[j];
		j++;
		inOrderTraverse(Forests[i].Right);
	}
	else return;
}

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}