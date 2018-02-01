#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表 */

List Insert(List L, ElementType X);

int main()
{
	List L;
	ElementType X;
	L = Read();
	scanf("%d", &X);
	L = Insert(L, X);
	Print(L);
	return 0;
}
List Read()
{
	int i,n,t;
	List L,New;
	L = (List)malloc(sizeof(struct Node));
	L->Next = NULL;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		New = (List)malloc(sizeof(struct Node));
		scanf("%d", &t);
		New->Data = t;
		L->Next = New;
		New->Next = NULL;
	}
	return L;
}
void Print(List L)
{
	while (L->Next)
	{
		printf("%d", L->Next->Data);
		L = L->Next;
	}
}
List Insert(List L, ElementType X)
{
	List T,P;
	T = (List)malloc(sizeof(struct Node));
	T->Data = X;
	T->Next = NULL;
	P = L;
	while (P->Next)
	{
		if (X <= P->Next->Data)
		{
			T->Next = P->Next;
			P->Next = T;
		}
		else if (X > P->Next->Data)
		{
			P = P->Next;
		}
	}
	return L;
}
