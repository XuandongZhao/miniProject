#include<stdio.h>
#ifndef _list_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P,List L );
Position Find(ElementType X,List L);
void Delete(ElementType X ,List L);
Position FindPrevious(ElementType X,List L);
void Insert(ElementType X,List L,Position P);
void DeleteList (List L);
Position First(List L);
Position Header(List L);
Position Advance(Position P);
ElementType Retrive(Position P);
#endif
struct Node
{
	ElementType Element;
	Position Next;
};

int IsEmpty(List L)
{
	
	return L->Next==NULL;
} 
 
int Islast(Position P,List L)
{
	return P->Next==NULL;
} 
 
Position Find(ElementType X,List L)
{
	Position P;
	P=L->Next ;
	while(P!=NULL&&P->Element!=X)
	P=P->Next;
	return P;	
}

void Delete(ElementType X,List L)
{
	Position P,	TmpCell;
	P=FindPrevious(X,L);
	if(!Islast(P,L))
	{
		TmpCell=P->Next;
		P->Next=TmpCell->Next;
		free(TmpCell);
	}
}


//Ñ°ÕÒº¯Êý 
Position FindPrevious(ElementType X,List L)
{
	Position P;
	P=L;
	while(P->Next!=NULL&&P->Next->Element!=X)
	P=P->Next;
	return P;
}


//²åÈëº¯Êý 
void Insert(ElementType X,List L,Position P)
{
	Position TmpCell;
	TmpCell=malloc(sizeof(struct Node));
	if(TmpCell==NULL)
	FataError("out of space!!!");
	TmpCell->Element=X;
	TmpCell->Next=P->Next;
	P->Next=TmpCell;
}
