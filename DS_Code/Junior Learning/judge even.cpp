#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrNode;
typedef PtrNode List;
typedef PtrNode Position;	
struct Node {
    void *pData;	//void pointer to achieve the function
	int Type;	//record the data's type
	Position pNext;	// point to next Node
};
enum { Int, Float, Double, Char, String };
// int 0, float 1, double 2, char 3,string 4
void ListPrint(List L);	//print the content of the List
List ListCreate(List L);	//create the List
List ListInsert(List L, int Type, int K, void *pNew);	//insert a Node into the List
List ListInsertFront(List L, int Type, void *pNew);	//insert a Node in the front of the List
List ListInsertBack(List L, int Type, void *pNew);	//insert a Node at the back of the List
List ListDelete(List L,int K);	//delete the List
List ListDeleteFront(List L);	//delete the first Node
List ListDeleteBack(List L);	//delete the last Node
List ListReverse(List L);	//reverse the List
List ListDestroy(List L);	//destroy the List
List ListUnion(List L1, List L2);	//unite two different List

int main()
{
	List L,New;
	int Node1 = 1;
	float Node2 = 2.0;
	double Node3 = 3.0;
	char Node4 = 'a';
	char *Node5 = 'String';

	L = ListCreate(L);
	New = ListCreate(New);
	L = ListInsertFront(L, Int, &Node1);
	ListPrint(L);
	L = ListInsertBack(L, Float, &Node2);
	ListPrint(L);
	L = ListInsert(L, Double, 2, &Node3);
	ListPrint(L);
	L = ListReverse(L);
	ListPrint(L);
	New = ListInsertFront(New, Char, &Node4);
	ListPrint(New);
	New = ListInsertBack(New, String, &Node5);
	ListPrint(New);
	L = ListUnion(L, New);
	ListPrint(L);
	L = ListDeleteFront(L);
	ListPrint(L);
	L = ListDelete(L, 3);
	ListPrint(L);
	L = ListDeleteBack(L);
	ListPrint(L);
	L = ListDestroy(L);
	ListPrint(L);
	return 0;
}

List ListCreate(List L)	//create a List and return the point to the first Node
{
	L = (List)malloc(sizeof(struct Node));
	L->pNext = NULL;
	return L;
}
List ListInsert(List L, int Type, int K, void *pNew)	//insert a Node to a specific position
{
	Position Place, New;	
	Place = ListFind(L, K);	//find the position first
	if (Place == NULL)
		printf("Can't find the Node");	//if can not find the place 
	else
	{
		New = (List)malloc(sizeof(struct Node));	//malloc a new space
		*(New->pData) = *pNew;	//initialize the New Node
		New->Type = Type;
		New->pNext = Place->pNext;
		Place->pNext = New;
	}
	return L;	//return the New Node
}
List ListInsertFront(List L,int Type,void *pNew)	//insert the Node into the Front of the List
{
	return ListInsert(L, Type, 1, pNew);
}	
List ListInsertBack(List L, int Type, void *pNew)	//insert the Node into the back of the List 
{
	int K;
	K = ListLength(L);
	L = ListInsert(L, Type, K, pNew);
	return L;
}
int ListLength(List L)	//return the length of the List
{
	List rear;	//pointer point to rear
	int count;	//count the length
	rear = L;
	count = 0;
	while (rear != NULL)
	{
		cout++;
		rear = rear->pNext;	//move back
	}
	return count;
}
List ListDelete(List L, int K)	//delete a Node from the List
{
	Position Place, Old;	//Old point to the old List
	if (K == 0)
		return L;
	else
	{
		Place = ListFind(L, K);	//find the right place
		Old = Place->pNext;	//find the next Node
		if (Place != NULL&&Old != NULL)	//delete the Node by change the pointer
		{
			Place->pNext = Old->pNext;
			Free(Old);
		}
		else
			printf("It is a not ligal palce");
	}
	return L;
}
List ListDeleteFront(List L)
{
	return ListDelete(L, Type, 1, pOld);
}
List ListDeleteBack(List L)
{
	int K;
	K = ListLength(L);
	L = ListDelete(L, Type, K, pNew);
	return L;
}
List ListFind(List L, int K)	//find the right place of the Node
{
	Position Place;
	Place = L;
	for (int i = 1; i < K; i++)	//use the for loop to find it
	{
		if (Place != NULL)
			Place = Place->pNext;
		else
		{
			printf("The Node doesn't exist.");
			return NULL;
		}
	}
	return Place;	//return the right place
}
List ListReverse(List L)	//reverse the List
{
	List New, Old, Temp;	//use three pointer
	New = L->pNext;	//New represent the New List
	if (New->pNext != NULL)
	{
		Old = New->pNext;
		while (Old != NULL)	//Old represent the Old List
		{
			Temp = Old->pNext;	//temp is the Node we handle now
			Old->pNext = New;
			New = Old;
			Old = Temp;	//move these pointers
		}
		L->pNext->pNext = Old;	//the first Node point to NULL
		L->pNext = New;	//L->Next point to new List
		return L;
	}
	else
		return L;
}
List ListDestroy(List L)	//destory the List
{
	List Rear, Temp;
	Temp = L;
	while (Temp)	//Temp is the Node we handle now
	{
		Rear = Temp->pNext;
		Free(Temp);
		Temp = Rear;
	}
	return Temp;
}
List ListUnion(List L1, List L2)	//Union two List
{
	List Rear;
	int Length;
	Length = ListLength(L1);	//get the length of the List1
	Rear = ListFind(L1, Length);
	Rear->pNext = L2->pNext;	//because we use an empty head
	return L1;
}
void ListPrint(List L)
{
	List PtrL;
	if (L->pNext == NULL)
		printf("the List is empty");
	else 
	{
		PtrL = L->pNext;
		while (PtrL)
		{
			switch (PtrL->Type)
			{
			case Int:
				printf("%d ", *(int*)PtrL->pData);
				break;
			case Float:
				printf("%lf ", *(float*)PtrL->pData);
				break;
			case Double:
				printf("%lf ", *(double*)PtrL->pData);
				break;
			case Char:
				printf("%c ", *(char*)PtrL->pData);
				break;
			case String:
				printf("%s ", *(char*)PtrL->pData);
			}
			PtrL = PtrL->pNext;
		}
	}
	printf("\n");
}