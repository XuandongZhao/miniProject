#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
        case push: 
            scanf("%d %d", &Sn, &X);
            if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
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
	else if (strcmp(opt, "end") == 0)
		return end;
}

void PrintStack( Stack S, int Stacknum )
{
	int i,j;
	
	if(Stacknum == 1)
	{
		printf("Pop from Stack 1: ");
		for(i=S->Top1;i>=0;i--)
		{
			printf("%d ",S->Array[i]);
		}
		printf("\n");
	}
	
	else 
	{
		printf("Pop from Stack 2: ");
		for(i=S->Top2;i<S->Capacity;i++)
		{
			printf("%d ",S->Array[i]);
		}
		printf("\n");
	}
}

Stack CreateStack( int MaxElements )
{
	Stack S;
	S = (Stack)malloc(sizeof(struct StackRecord));
	int *D;
	D = (int*)malloc(sizeof(int) *MaxElements);
	S->Capacity = MaxElements;
	S->Top1 = -1;
	S->Top2 = S->Capacity;
	S->Array = D;
	return S;	
}

int IsEmpty( Stack S, int Stacknum )
{
	if(Stacknum == 1)
	{
		if(S->Top1 == -1)
		return 1;
	}
	
	else 
	{
		if(S->Top2 == S->Capacity)
		return 1;
	}
	return 0;
}

int IsFull( Stack S )
{
	if(S->Top2-1 == S->Top1)
	return 1;
	else 
	return 0;
} 

int Push( ElementType X, Stack S, int Stacknum )
{
	if(IsFull(S))
	{
		return 0;
	}
	
	if(Stacknum == 1)
	{
		S->Top1++;
		S->Array[S->Top1] = X;
	}
	else if(Stacknum == 2)
	{
		S->Top2--;
		S->Array[S->Top2] = X;
	}	
	return 1;
}

ElementType Top_Pop( Stack S, int Stacknum )
{
	int temp;
	if(IsEmpty(S,Stacknum))
	{
		return ERROR;
	}
	
	if(Stacknum == 1)
	{
		temp = S->Array[S->Top1];
		S->Top1--;
	}
	else if(Stacknum == 2)
	{
		temp = S->Array[S->Top2];
		S->Top2++;
	}
	return temp;
}
