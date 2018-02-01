#include<stdio.h>
#include<stdlib.h>

struct Node {
	ElementType Element;
	List Next;
};
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

List MakeEmpty(List L)
{
	List L;
	L = (*PtrToNode)malloc(sizeof(struct Node));
	L->Next = NULL;
	return L;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

int IsLast(Position P, List L)
{
	return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
	Position P;
	P = L->Next;
	/*while(P != NULL)
	{
	if(P->Element == X)
	return P;
	else P = P->Next;
	}*/
	while (P != NULL && P->Next != X)
		P = P->Next;
	return P;
}

void Delete(ElementType X, List L)
{
	Position P, Temp;
	P = L->Next;
	while (P->Next != NULL&&P->Next->Element != X)
		P = P->Next;
	if (!IsLast(P, L))
	{
		Temp = P->Next;
		P->Next = Temp->Next;
		free(Temp);
	}
}

void Insert(ElementType X, Position P, List L)
{
	Position Temp;
	Temp = (List)malloc(sizeof(struct Node));
	Temp->Element = X;
	Temp->Next = P->Next;
	P->Next = Temp;
}

void DeleteList(List L)
{
	Position P,Temp;
	P = L->Next;
	L->Next = NULL;
	while (P != NUll)
	{
		Temp = P->Next;
		free(P);
		P = Temp;
	}
}
