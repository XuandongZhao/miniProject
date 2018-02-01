#include<stdio.h>
#include<stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position Tree; 
struct TNode
{
	ElementType c;
	Tree Left;
	Tree Right;
};


Tree CreateTree();
void levelorder(Tree T);
int main()
{
	Tree T;
	T = CreateTree();
	levelorder(T);
	return 0;
}
Tree CreateTree()
{
	char c;
	Tree T;
	scanf("%c", &c);
	if (c == '#')
	{
		T = NULL;
		return T;
	}
	else
	{
		T->c = c;
		T->Left = CreateTree();
		T->Right = CreateTree();
	}
	return T;
}

void levelorder(Tree T)
{
	Tree a[20];
	int i;
	int end, front;
	i = end = front = 0;
	a[0] = T;
	while (i <= end)
	{
		if(a[i]->Left)
		a[++end] = a[i]->Left;
		if(a[i]->Right)
		a[++end] = a[i]->Right;
		i++;
	}
	for (front = 0; front<=end ; front++)
	{
		printf("%c", a[front]->c);
	}
}

