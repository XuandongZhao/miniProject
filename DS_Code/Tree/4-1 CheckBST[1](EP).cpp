#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode {
	int Key;
	BinTree Left;
	BinTree Right;
};

BinTree BuildTree(); /* details omitted */
int CheckBST(BinTree T, int K);

int main()
{
	BinTree T;
	int K, out;

	T = BuildTree();
	scanf("%d", &K);
	out = CheckBST(T, K);
	if (out < 0)
		printf("No.  Height = %d\n", -out);
	else
		printf("Yes.  Key = %d\n", out);

	return 0;
}
BinTree BuildTree()
{
	int i;
	BinTree T;
	scanf("%d", &i);
	if (i == 0)
	{
		T = NULL;
	}
	else
	{
		T = (BinTree)malloc(sizeof(struct TNode));
		T->Key = i;
		T->Left = BuildTree();
		T->Right = BuildTree();
	}
	return T;
}
int Height(BinTree T);
int find(BinTree T, int K);
int isBST(BinTree T);
void traversalTree(BinTree T, int *pos, int array[]);
int find(BinTree T, int K);
int CheckBST(BinTree T, int K)
{
	if (isBST(T))
	{
		return find(T, K);
	}
	else
	{
		return -Height(T);
	}
}
int isBST(BinTree T)
{
	static BinTree prev = NULL;
	if (T)
	{
		if (!isBST(T->Left))
			return 0;
		if (prev != NULL && T->Key <= prev->Key)
			return 0;

		prev = T;
		return isBST(T->Right);
	}
	return 1;
}

int Height(BinTree T)
{
	if (T == NULL) return 0;
	else
	{
		int m = Height(T->Left);
		int n = Height(T->Right);
		return (m > n) ? (m + 1) : (n + 1);
	}
}

int find(BinTree T, int K)
{
	int i,j;
	j = 0;
	int *pos;
	pos = &j;
	int a[300],b[300];
	traversalTree(T, pos, a);
	j = a[*pos-K];
	return j;
}

void traversalTree(BinTree T, int *pos, int array[])
{
	if (T == NULL)
		return;

	traversalTree(T->Left, pos, array);
	array[(*pos)++] = T->Key;
	traversalTree(T->Right, pos, array);
}