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

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

void Print(Polynomial p)
{
	Polynomial q;
	q=p;
	if(p)
	while(q)
	{
		printf("%d %d ",q->Coefficient,q->Exponent);
		q=q->Next;
	}
	printf("\n");
}

Polynomial Read()
{
	int n,c,d;
	Polynomial head,pre,tear,temp;
	scanf("%d",&n);
	pre=tear=head=(Polynomial)malloc(sizeof(struct Node));
	head->Next=NULL;
	while(n--)
	{
		tear=(Polynomial)malloc(sizeof(struct Node));
		tear->Next=NULL;
		scanf("%d%d",&tear->Coefficient,&tear->Exponent);
		pre->Next=tear;
		pre=tear;
	}
	temp=head;
	head=head->Next;
	free(temp);
	return head;
}

Polynomial Add( Polynomial a, Polynomial b )
{
	Polynomial result,p1,p2,temp;
	int x,y,sum;

	result=(Polynomial)malloc(sizeof(struct Node));
	p1=p2=result;
	result->Next=NULL;
	while(a&&b)
	{
		if(a->Exponent==b->Exponent)
		{
			sum=a->Coefficient+b->Coefficient;
			if(sum)
			{
				p1=(Polynomial)malloc(sizeof(struct Node));
				p1->Next=NULL;
				p1->Coefficient=sum;
				p1->Exponent=a->Exponent;
				p2->Next=p1;
				p2=p1;				
			}
			a=a->Next;
			b=b->Next;
		}
		else if(a->Exponent>b->Exponent)
		{
			p1=(Polynomial)malloc(sizeof(struct Node));
			p1->Next=NULL;
			p1->Coefficient=a->Coefficient;
			p1->Exponent=a->Exponent;
			p2->Next=p1;
			p2=p1;	
			a=a->Next;	
		}
		else if(a->Exponent<b->Exponent)
		{
			p1=(Polynomial)malloc(sizeof(struct Node));
			p1->Next=NULL;
			p1->Coefficient=b->Coefficient;
			p1->Exponent=b->Exponent;
			p2->Next=p1;
			p2=p1;
			b=b->Next;
		}
	}
	for(;a;a=a->Next)
	{
		p1=(Polynomial)malloc(sizeof(struct Node));
		p1->Next=NULL;
		p1->Coefficient=a->Coefficient;
		p1->Exponent=a->Exponent;
		p2->Next=p1;
		p2=p1;
	}
	for(;b;b=b->Next)
	{
		p1=(Polynomial)malloc(sizeof(struct Node));
		p1->Next=NULL;
		p1->Coefficient=b->Coefficient;
		p1->Exponent=b->Exponent;
		p2->Next=p1;
		p2=p1;
	}
	
	temp=result;
	result=result->Next;
	free(temp);
	return result;
}