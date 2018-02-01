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

    Polynomial Add( Polynomial a, Polynomial b )  
    {  
        Polynomial sum;  
        sum=(Polynomial)malloc(sizeof(struct Node));  
        sum->Next=NULL;  
        a=a->Next;  
        b=b->Next;  
        Polynomial temp=sum;  
        while(a&&b){  
            if(a->Exponent>b->Exponent){  
                temp->Next=a;  
                a=a->Next;  
                temp->Next->Next=NULL;  
                temp=temp->Next;  
      
            }  
            else if(b->Exponent>a->Exponent){  
                temp->Next=b;  
                b=b->Next;  
                temp->Next->Next=NULL;  
                temp=temp->Next;  
            }  
            else{  
                Polynomial t;  
                t=(Polynomial)malloc(sizeof(struct Node));  
                t->Coefficient=a->Coefficient+b->Coefficient;  
                t->Exponent=a->Exponent;  
                t->Next=NULL;  
                if(t->Coefficient!=0){  
                    temp->Next=t;  
                    temp=temp->Next;  
                }  
                a=a->Next;  
                b=b->Next;  
            }  
        }  
        while(a){  
            temp->Next=a;  
            temp=temp->Next;  
            a=a->Next;  
        }  
        while(b){  
            temp->Next=b;  
            temp=temp->Next;  
            b=b->Next;  
        }  
        temp->Next=NULL;  
        return sum;  
    }  
