#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

Operation GetOp()
{
	char opt[7];
	scanf("%s", opt);
	if (strcmp(opt, "push") == 0)
		return push;
	else if (strcmp(opt, "pop") == 0)
		return pop;
	else if (strcmp(opt, "inject") == 0)
		return inject;
	else if (strcmp(opt, "eject") == 0)
		return eject;
	else if (strcmp(opt, "end") == 0)
		return end;
}

void PrintDeque(Deque D)
{
	PtrToNode temp;

	printf( "Inside deque: " );
	temp = D->Front->Next;
	while (temp != NULL )
	{
		printf("%d ", temp->Element);
		temp = temp->Next;
	}

	printf("\n-----------\n");
}

Deque CreateDeque()
{
	Deque D;
	PtrToNode P;
	D=(Deque)malloc(sizeof(struct DequeRecord));
	P=(PtrToNode)malloc(sizeof(struct Node));
	
	if(D&&P)
	{
		P->Next=NULL;
		P->Last=NULL;
		D->Front=D->Rear=P;
	}
	return D;
}

int Push( ElementType X, Deque D )
{
	PtrToNode P;
	P = (PtrToNode)malloc(sizeof(struct Node));
	if(!P)
	{
		return 0;
	}
	
	P->Element = X;
	P->Last = D->Front;
	
	if(D->Front == D->Rear)
	{
		D->Rear = P;
		P->Next = NULL;
	}
	else
	{
		P->Next = D->Front->Next;
		D->Front->Next->Last = P;
	}
	D->Front->Next = P;
	return 1;
}

int Inject( ElementType X, Deque D )
{
	PtrToNode P;
	P = (PtrToNode)malloc(sizeof(struct Node));
	if(!P)
	{
		return 0;
	}
	
	P->Element = X;
	
	if(D->Front == D->Rear)
	{
		P->Last = D->Front;
		D->Front->Next = P;
	}
	else
	{
		P->Last = D->Rear;
		D->Rear->Next = P;
	}
	
	D->Rear = P;
	P->Next = NULL;
	return 1;
}

ElementType Pop( Deque D )
{
	int i;
	if(D->Front == D->Rear)
	{
		return ERROR;
	}
	
	i = D->Front->Next->Element;

	PtrToNode d; 
	d = D->Front->Next;
	
	if(D->Front != D->Rear)
	{
		if(!d->Next)
		{
			D->Front->Next = NULL;
			D->Rear = D->Front;
		}
		else
		{
			D->Front->Next = d->Next;
			d->Next->Last = D->Front;
		}
		free(d);
		return i;
	}
	else return ERROR;
}

ElementType Eject( Deque D )
{
	int i;
	i = D->Rear->Element;
	PtrToNode d;
	d = D->Rear;
	
	if(D->Front != D->Rear)
	{
		D->Rear = d->Last;
		D->Rear->Next = NULL;
		free(d);
		return i;
	}
	
	else return ERROR;
}
