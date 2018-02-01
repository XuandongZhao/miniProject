#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );
void Attach(int c,int e,Polynomial *pRear);

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

void Attach(int c,int e,Polynomial *pRear)
{
	Polynomial P;
	P=(Polynomial)malloc(sizeof(struct Node));
	P->Coefficient=c;
	P->Exponent=e;
	P->Next=NULL;
	(*pRear)->Next=P;
	*pRear=P;
}

Polynomial Read()
{
	int N;
	int c,e;
	Polynomial Rear,P,t;
	P=(Polynomial)malloc(sizeof(struct Node));
	//P->Next=NULL;
	Rear=P;
	
	scanf("%d",&N);
	while(N--)
	{
		scanf("%d%d",&c,&e);
		Attach(c,e,&Rear);
	}
	t=P;
	P=P->Next;
	free(t);
	return P;	
} 

Polynomial Add(Polynomial a,Polynomial b)
{
	Polynomial front,rear,temp;
	int sum;
	rear=(Polynomial)malloc(sizeof(struct Node));
	rear->Next=NULL;
	front=rear;
	//while(a&&b)
	for(;(a!=NULL)&&(b!=NULL);)
	{
		if (a->Exponent==b->Exponent)
		{
			sum=a->Coefficient+b->Coefficient;
			if(sum)
			{
				Attach(sum,a->Exponent,&rear);
				a=a->Next;
				b=b->Next;
			}
		}
		else if(a->Exponent>b->Exponent)
		{
			Attach(a->Coefficient,a->Exponent,&rear);
			a=a->Next;
		}
		else if(a->Exponent<b->Exponent)
		{
			Attach(b->Coefficient,b->Exponent,&rear);
			b=b->Next;
		}
	}
		for(;a;a=a->Next)Attach(a->Coefficient,a->Exponent,&rear);
		for(;b;b=b->Next)Attach(b->Coefficient,b->Exponent,&rear);
	
		rear->Next=NULL;
		temp=front;
		front=front->Next;
		free(temp);
		return front;
	 
}

void Print( Polynomial P )
{
	int flag=0;
	if(!P)
	{
		printf("0 0\n");
		return;
	}
	while (P)
	{
		if(!flag)
		flag=1;
		else 
		printf(" ");
		printf("%d %d",P->Coefficient,P->Exponent);
		P=P->Next;
	}
}




