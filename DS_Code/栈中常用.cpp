#define SATCKINSREMENT 10;
 
Push(sqStack *s,ElemType e)
{
	if(s->top-s->base>=stackSize)
	{
		s->base=(ElemType *)realloc(s->base,(s->stackSize +SATCKINSREMENT)*sizeof(ElemType));
		if(!s->base)
		exit(0);
		s->top=s->base+s->stackSize;
		s->stackSize=s->stackSize+SATCKINSREMENT;
	}
	*(s->top)=e;
	s->top++;
}

void Pop(sqStack *s,ElemType *e)
{
	if(s->top==s->base)
	return;
	*e=*--(s->top);
}

void ClearStack(sqStack *s)
{
	s->top=s->base;
}

void DestroyStack(sqStack *s)
{
	int i,len;
	len=s->stackSize;
	for(i=0;i<len;i++)
	{
		free(s->base);
		s->base++;	
	}
	s->base=s->top=NULL;
	s->stackSize=0;
} 

int StackLen(sqStack s)
{
	return(s.top-s.base);
}

Push()
{
	
}