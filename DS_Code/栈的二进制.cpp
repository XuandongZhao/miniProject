#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREAMENT 10

typedef char ElemType;
typedef struct 
{
	ElemType *base;
	ElemType *top;
	int stackSize; 
} sqStack;

void InitStack(sqStack *s);
void Push(sqStack *s,ElemType e);
void Pop(sqStack *s,ElemType *e);
int StackLen(sqStack s);

void InitStack(sqStack *s)
{
	s->base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!s->base)
	exit(0);
	s->top=s->base;
	s->stackSize=STACK_INIT_SIZE;
}

void Push(sqStack *s,ElemType e)
{
	if((s->top-s->base)>=s->stackSize)
	{
		s->base=(ElemType *)realloc(s->base,(s->stackSize+STACKINCREAMENT)*sizeof(ElemType));
		if(!s->base)
		exit(0);
	}
	*(s->top)=e;
	s->top++;
}

void Pop(sqStack *s,ElemType *e)
{
	if(s->top==s->base)
	{
		return;
	}
	*e=*--(s->top);
}

int StackLen(sqStack s)
{
	return (s.top-s.base);
}

int main()
{
	ElemType c;
	sqStack s;
	int len,i,sum;
	sum=0;
	InitStack (&s); 
	printf("请输入二进制数:\n");
	scanf("%c",&c);
	while(c!='#')
	{
		Push(&s,c);
		scanf("%c",&c);
	}
	getchar();
	len =StackLen(s);
	for(i=0;i<len;i++)
	{
		Pop(&s,&c);
		sum=sum+(c-48)*pow(2,i);
	}
	printf("%d\n",sum);
	return 0;
}