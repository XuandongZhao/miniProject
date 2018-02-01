void Attach(int c,int d,Polynomial *pRear);
void Attach(int c,int d,Polynomial *pRear)
{
	Polynomial P;
	
	P=(Polynomial)malloc(sizeof(struct Node));
	P->Coefficient=c;
	P->Exponent=d;
	P->Next=NULL;
	(*pRear)->Next=P;
	*pRear=P;
}

Polynomial Add( Polynomial a, Polynomial b )
{
	Polynomial front,rear,temp,c,d;
	int sum;
	c=a;
	d=b;
	//p=(Polynomial)malloc(sizeof(struct Node));
	
	rear=(Polynomial)malloc(sizeof(Polynomial));
	rear->Next=NULL;
	front=rear;
	
	while(c&&d)
	{
		if(c->Exponent==d->Exponent)
		{
			sum=c->Coefficient+d->Coefficient;
			if(sum)
			{
				Attach(sum,c->Exponent,&rear);
			//	p->Coefficient=sum;
			//	p->Exponent=a->Exponent;
			//	p->Next=NULL;
			//	rear->Next=p;
				c=c->Next;
				d=d->Next;
			}
		}
		else if(c->Exponent>d->Exponent)
		{
			Attach(c->Coefficient,c->Exponent,&rear);
		//	p->Coefficient=a->Coefficient;
		//	p->Exponent=a->Exponent;
		//	p->Next=NULL;
		//	rear->Next=p;
			c=c->Next;
		}
		else if(c->Exponent<d->Exponent)
		{
			Attach(d->Coefficient,d->Exponent,&rear);
			//p->Coefficient=b->Coefficient;
			//p->Exponent=b->Exponent;
			//p->Next=NULL;
			//rear->Next=p;
			d=d->Next;
		}
	}
	//for(;c;c=c->Next)
	while(c)
	{
			/*p->Coefficient=a->Coefficient;
			p->Exponent=a->Exponent;
			p->Next=NULL;
			rear->Next=p;*/
			Attach(c->Coefficient,c->Exponent,&rear);
	}
	//for(;d;d=d->Next) 
	while(d)
	{
		/*	p->Coefficient=b->Coefficient;
			p->Exponent=b->Exponent;
			p->Next=NULL;
			rear->Next=p;*/
			Attach(d->Coefficient,d->Exponent,&rear);	
	}
	rear->Next=NULL;
	temp=front;
	front=front->Next;
	free(temp);
	return front;
}


