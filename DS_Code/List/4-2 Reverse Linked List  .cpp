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

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
	int N,i;
	List P,rear,temp,R;
	scanf("%d",&N);
	P=(List)malloc(sizeof(struct Node));
	rear=P;
	while(N--)
	{
		scanf("%d",&i);
		R=(List)malloc(sizeof(struct Node));
		R->Element=i;
		R->Next=NULL;
		R=rear->Next;
		rear=R;
	} 
	temp=P;
	P=P->Next;
	free(temp);
	return P;	
}

void Print( List P )
{
	int flag=0;
	if(!P)
	{
		printf("0\n");
		return;
	}
	while (P)
	{
		if(!flag)
		flag=1;
		else 
		printf(" ");
		printf("%d ",P->Element);
		P=P->Next;
	}
}

List Reverse( List L )  
{  
	List front, rear;
	int a[80];
	int i = 0;
	front = L->Next;
	rear = L->Next;
	while(front)
	{
		a[i] = front->Element;
		i++;
		front = front->Next;
	}
	i--;
	for(;i>=0;i++)
	{
		rear->Element = a[i];
		rear = rear->Next;
	}
	return L;
}

