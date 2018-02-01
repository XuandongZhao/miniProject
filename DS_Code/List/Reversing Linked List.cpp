#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
	ElementType Element;
	Position Next;
};

List Insert(List L,int X); /* details omitted */
void Print(List L); /* details omitted */
List Reverse(List L,int K);

int main()
{
	List L1, L2;
	int address, N, X;
	L1 = (List)malloc(sizeof(struct Node));
	scanf("%d", &address);
	L1->Next = address;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &X);
		L1 = Insert(L1, X);
	}
	L2 = Reverse(L1);
	Print(L2);
	return 0;
}
void Print(List L)
{
	for (List Temp = L->Next; Temp != NULL; Temp = Temp->Next)
		printf("%d ", Temp->Element);
	printf("\n");
}