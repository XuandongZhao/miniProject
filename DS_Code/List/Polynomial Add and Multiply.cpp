#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node {
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print(Polynomial p); /* details omitted */
Polynomial Multiply(Polynomial a, Polynomial b);
Polynomial Add(Polynomial a, Polynomial b);
void Attach(int c, int e, Polynomial *pRear);

int main()
{
	Polynomial a, b, s1,s2;
	a = Read();
	b = Read();
	s1 = Multiply(a, b);
	s2 = Add(a, b);
	Print(s1);
	Print(s2);
	return 0;
}

void Attach(int c, int e, Polynomial *pRear)
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct Node));
	P->Coefficient = c;
	P->Exponent = e;
	P->Next = NULL;
	(*pRear)->Next = P;
	*pRear = P;
}

Polynomial Read()
{
	int N;
	int c, e;
	Polynomial Rear, P, t;
	P = (Polynomial)malloc(sizeof(struct Node));
	P->Next=NULL;
	Rear = P;

	scanf("%d", &N);
	while (N--)
	{
		scanf("%d%d", &c, &e);
		Attach(c, e, &Rear);
	}
	t = P;
	P = P->Next;
	free(t);
	return P;
}

Polynomial Add(Polynomial a, Polynomial b)
{
	Polynomial front, rear, temp;
	int sum;
	a = a->Next;
	b = b->Next;
	rear = (Polynomial)malloc(sizeof(struct Node));
	rear->Next = NULL;
	front = rear;
	while(a&&b)
	{
		if (a->Exponent == b->Exponent)
		{
			sum = a->Coefficient + b->Coefficient;
			if (sum)
			{
				Attach(sum, a->Exponent, &rear);
				a = a->Next;
				b = b->Next;
			}
		}
		else if (a->Exponent>b->Exponent)
		{
			Attach(a->Coefficient, a->Exponent, &rear);
			a = a->Next;
		}
		else if (a->Exponent<b->Exponent)
		{
			Attach(b->Coefficient, b->Exponent, &rear);
			b = b->Next;
		}
	}
	for (; a; a = a->Next)Attach(a->Coefficient, a->Exponent, &rear);
	for (; b; b = b->Next)Attach(b->Coefficient, b->Exponent, &rear);

	rear->Next = NULL;
	return front;
}

void Print(Polynomial P)
{
	int flag = 0;
	P = P->Next;
	if (!P)
	{
		printf("0 0\n");
		return;
	}
	while (P)
	{
		if (!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d", P->Coefficient, P->Exponent);
		P = P->Next;
	}
	printf("\n");
}

Polynomial Multiply(Polynomial a, Polynomial b)
{
	Polynomial front, rear, tempf,tempr,t1,t2,P,temp;
	int result;

	tempf = (Polynomial)malloc(sizeof(struct Node));
	tempf->Next = NULL;
	tempr = tempf;

	front = (Polynomial)malloc(sizeof(struct Node));
	front->Next = NULL;
	rear = front;

	t1 = a;
	t2 = b;
	if(!a||!b) return NULL;
	
	while (t2)
	{
		Attach(t1->Coefficient*t2->Coefficient, t1->Exponent+t2->Exponent, &rear);
		t2 = t2->Next;
	}
	t1 = t1->Next;
	while (t1)
	{
		t2 = b;
		while (t2)
		{
			Attach(t1->Coefficient*t2->Coefficient, t1->Exponent+t2->Exponent, &tempr);
			t2 = t2->Next;
		}
		front = Add(front, tempf);
		while(tempf)
		{
			free(tempf);
			tempf = tempf->Next; 
		}
		rear = front;
		t1 = t1->Next;
	}
	while(rear->Next)
	{
		rear = rear->Next;
	}
	rear->Next = NULL;

	return front;
}



