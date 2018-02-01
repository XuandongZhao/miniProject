#include<stdio.h>
#include<stdlib.h>
#define len sizeof(struct student)
struct student 
{
	long int num;
	float score;
	struct student * Next;
} ;
int n;
struct student *create();
struct student *create()
{
	struct student *head;
	struct student *p1,*p2;
	n=0;
	//p2=(struct student *)malloc(len);
	p1=(struct student *)malloc(len);
	scanf("%ld%f",&p1->num,&p1->score);
	head=NULL;
	p1=head;
	p2=head;
	while(p1->num!=0)
	{
		n++;
		if(n==1)head=p1;
		else p2->Next=p1;
		p1=(struct student *)malloc(len);
		scanf("%ld%f",&p1->num,&p1->score);
	}
	p2->Next=NULL;
	return head;
}
void print(struct student *head);
void print(struct student *head)
{
	struct student *p;
	p=head;
	if(head!=NULL) {
	while(p->Next!=NULL)
	{
		printf("%ld %f",p->num,p->score);
		p=p->Next;
	}}
}
int main()
{
	struct student * head;
	head=create();
	print(head);
}
