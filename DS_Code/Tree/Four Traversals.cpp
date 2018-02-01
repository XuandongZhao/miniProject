#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

BinTree CreatBinTree(); /* ÊµÏÖÏ¸½ÚºöÂÔ */
void InorderTraversal(BinTree BT);
void PreorderTraversal(BinTree BT);
void PostorderTraversal(BinTree BT);
void LevelorderTraversal(BinTree BT);

int main()
{
	BinTree BT = CreatBinTree();
	printf("Inorder:");    InorderTraversal(BT);    printf("\n");
	printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
	printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
	printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
	return 0;
}

BinTree CreatBinTree()
{
	char c;
	BinTree T;

	scanf("%c", &c);

	if (c == '#')
	{
		T = NULL;
	}
	else
	{
		T = (BinTree)malloc(sizeof(struct TNode));
		T->Data = c;
		T->Left = CreatBinTree();
		T->Right = CreatBinTree();
	}
	return T;
}
void InorderTraversal(BinTree BT)
{
	if (BT)
	{
		InorderTraversal(BT->Left);
		printf("%c ", BT->Data);
		InorderTraversal(BT->Right);
	}
}
void PreorderTraversal(BinTree BT)
{
	if (BT)
	{
		printf("%c ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}
void PostorderTraversal(BinTree BT)
{
	if (BT)
	{
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%c ", BT->Data);
	}
}
void LevelorderTraversal(BinTree BT) 
{
	BinTree q[100];
	BinTree p;
	int head = 0, tail = 0;
	if (!BT) return;
	if (BT) 
	{
		q[tail++] = BT;
		while (tail != head) 
		{
			p = q[head++];
			printf(" %c", p->Data);
			if (p->Left)     q[tail++] = p->Left;
			if (p->Right)    q[tail++] = p->Right;
		}
	}
}