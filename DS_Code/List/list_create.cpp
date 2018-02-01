#include<stdio.h>
#include<stdlib.h>
typedef struct Node * List;

struct Node{
	int num;
	List Next; 
};

List read();
void print(List l);

int main()
{
	int a;
	List i;
	i=read();
	print(i);
	return 0;
}

List read()
{
	List head,p1,p2;
	int i,n;
	scanf("%d",&n);
	p1=(List)malloc(sizeof(struct Node));
	p2=p1;
	head=p1;
	//scanf("%d",&p1->num);
	
	while(n--)
	{
		scanf("%d",&i);
		//p2->Next=p1;
		//p2=p1;
		p1=(List)malloc(sizeof(struct Node));
		p1->num=i;
		p1->Next=NULL;
		p2->Next=p1;
		p2=p1;
	}
	//p->Next=NULL;
	return head;
}

void print(List l)
{
	List p;
	p=l->Next;
	if(l!=NULL)
	do
	{
		printf("%d ",p->num);
		p=p->Next; 
	}while(p!=NULL);
}
