#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
	int n,number;
	List p1,p2,head,temp;
	p1=p2=head=(List)malloc(sizeof(struct Node));
	head->Next=NULL;
	scanf("%d",&n);
	while(n--)
	{
		p1=(List)malloc(sizeof(struct Node));
		p1->Next=NULL;
		scanf("%d",&number);
		p1->Element=number;
		p2->Next=p1;
		p2=p1;
	}
	//temp=head;
	//head=head->Next;
	//free(temp);
	return head;
} 

void Print(List L)
{
	List p;
	p=L;
	if(L)
	while(p)
	{
		printf("%d ",p->Element);
		p=p->Next;
	}
	printf("\n");
}

/*List Reverse (List L)
{
	List front,rear;
	int a[80];
	int i=0;
	front=L;
	rear=L;
	while(front)
	{
		a[i]=front->Element;
		i++;
		front=front->Next;
	} 
	i--;
	for(;i>=0;i--)
	{
		rear->Element=a[i];
		rear=rear->Next;
	}
	return L;
}*/
List Reverse(List L)
{
	List front,rear,temp;
	//temp=L;
	front=rear=temp=L->Next;
	//temp=temp->Next;
	front=temp;
	rear->Next=NULL;
	while(temp->Next)
	{
		temp=temp->Next;
		front->Next=rear;
		rear=front;
		front=temp;
	}
	temp->Next=rear;
	L->Next=temp;
	return L;
}

/*List Reverse(List L)
{
	List New;
	List p1,p2,rear,temp;
	rear=L;
	New=(List)malloc(sizeof(struct Node));
	New->Next=NULL;
	
	while(L)
	{
		L=L->Next;
		rear->Next=New;
		New=rear;
		rear=L; 		
	}
	
	p1=New;
	p2=p1->Next;
	while(p2)
	{
		if(p2->Next==NULL)
		{
			p1->Next=NULL;
			free(p2);
			break;
		}
		else
		{
			p1=p2;
			p2=p1->Next;
		}
	}
	L->Next=New;
 	L->Next=L->Next->Next;
 	
 	free(New);
	//free(New);
	//temp->Next=New;
	return L;
	//return New;
}*/

/*List Reverse( List L )  
{  
    List oldlist=L->Next;  
    List newlist;  
    List temp,tempnew,tempold;
    
    newlist=(struct Node*)malloc(sizeof(struct Node));  
    newlist->Next=NULL;  
    while(oldlist)
	{  
        temp=oldlist->Next;  
        oldlist->Next=newlist->Next;  
        newlist->Next=oldlist;  
        oldlist=temp;  
    }  
 
    tempnew=newlist->Next;  
    tempold=L;  
    while(tempnew)
	{  
        tempold->Next=tempnew;  
        tempold=tempold->Next;  
        tempnew=tempnew->Next;  
    }  
    tempold->Next=NULL;  
    return newlist;  
}*/
