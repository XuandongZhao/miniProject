#include<stdio.h>
#include<stdlib.h>
void add(List *head,int number);
typedef struct _node Node;

typedef struct _list{
	Node* head;
}List;

struct _node
{
	int value;
	struct _node* Next;
};

int main()
{
	List list;
	list.head=NULL;
	
	int number;
	scanf("%d",&number);
	while(number)
	{
		add(&head,number);
	}
} 

void add(List *phead,int number)
{
	List p=(List)malloc(sizeof(struct Node));
	p->value=number;
	p->Next=NULL;
	List last;
	last=head;
	if(last)
		{
		while(last->Next)
		{
			last=last->next;
		}
		last->Next=p;
	    }
}
