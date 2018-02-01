#include <stdio.h>
#include <stdlib.h>


#define Null -1
#define MaxTree 200

typedef struct node TNode;
struct node
{
	int Element;
	int right;
	int left;
};
typedef TNode* Tree;

int a[MaxTree];
int q =0;
struct node T[MaxTree];

int BuildTree(Tree T, int N);
void inorderBuild(int i); 
void Print(int R, Tree T);

int main()
{
	int R, N;
	int i, j, temp;
	Tree t;
	//freopen("inn.txt","r",stdin); 
	scanf("%d", &N);
	R = BuildTree(T, N);	//通过结构数组进行建树 

	for (i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j < N - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}//冒泡排序进行中序排列
	 
	inorderBuild(R);//将元素填入数组 
	Print(R, T)//层序遍历输出 
	return 0;
}

int BuildTree(Tree T, int N)
{
	int i, cl, cr;
	int check[MaxTree];
	int Root=0;

	if (N)
	{
		for (i = 0; i < N; i++)
			check[i] = 0;
		for (i = 0; i < N; i++)
		{
			scanf("%d%d", &cl, &cr);
			if (cl != -1)
			{
				T[i].left = cl;
				check[T[i].left] = 1;
			}
			else T[i].left = Null;
			if (cr != -1)
			{
				T[i].right = cr;
				check[T[i].right] = 1;
			}
			else T[i].right = Null;
		}
		for (i = 0; i < N; i++)
		{
			if (!check[i]) break;
		}
		Root = i;
	}
	return i;
}

void inorderBuild(int i)
{
	if (i >= 0)
	{
		inorderBuild(T[i].left);
		T[i].Element = a[q++];
		inorderBuild(T[i].right);
	}
	else
		return;
}

void Print(int R, Tree T)
{
	if (!T)
		return;
	int front, end, i;
	front = end = i = 0;
	Tree q[100];
	q[0] = T+R;
	while (i <= end)
	{
		if (q[i]->left > 0)
			q[++end] = T + q[i]->left;
		if (q[i]->right > 0)
			q[++end] = T + q[i]->right;
		i++;
	}
	for (i = front; i < end; i++)
	{
		printf("%d ", q[i]->Element);
	}
	printf("%d",q[i]->Element);
}

