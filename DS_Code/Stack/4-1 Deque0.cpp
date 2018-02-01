#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

Deque CreateDeque(){
Deque D;
PtrToNode head;

head =(PtrToNode) malloc( sizeof( struct Node ) );
D =(Deque) malloc( sizeof( struct DequeRecord ) );
if( D&&head ){
head->Last = head->Next = NULL;
D->Front = D->Rear = head;
}
return D;
/*else
FatalError( "out of space!!!" );*/
}

int Push( ElementType X, Deque D ){
PtrToNode p;

p = (PtrToNode)malloc( sizeof( struct Node ) );
if( !p ){
/*FatalError( "out of space!!!" );*/
return 0;
}
p->Element = X;
p->Last = D->Front;
if( D->Rear == D->Front ){
D->Rear = p;
p->Next = NULL;
}
else{
p->Next = D->Front->Next;
D->Front->Next->Last = p;
}
D->Front->Next = p;
return 1;
}

ElementType Pop( Deque D ){
ElementType X;
PtrToNode p;

if ( D->Rear == D->Front ){
/*Error( "empty deque!!!" );*/
return ERROR;
}
p = D->Front->Next;
X = p->Element;
if ( !p->Next ){
D->Front->Next = NULL;
D->Rear = D->Front;
}
else{
p->Last->Next = p->Next;
p->Next->Last = p->Last;
}
free( p );
return X;
}

int Inject( ElementType X, Deque D ){
PtrToNode p;

p = (PtrToNode)malloc( sizeof( struct Node ) );
if( !p ){
/*FatalError( "out of space!!!" );*/
return 0;
}
p->Element = X;
p->Last = D->Rear;
p->Next = NULL;
D->Rear = D->Rear->Next = p;

return 1;
}

ElementType Eject( Deque D ){
ElementType X;
PtrToNode p;

if ( D->Rear == D->Front ){
/*Error( "empty deque!!!" );*/
return ERROR;
}
p = D->Rear;
X = p->Element;
p->Last->Next = NULL;
D->Rear = p->Last;
free( p );
return X;
}

void Error( char *s ){
printf( "Error:%s\n",s );
}
void FatalError( char *s ){
printf( "FatalError:%s\n",s );
}

Operation GetOp()
{
char opt[7];
scanf("%s", opt);
if (strcmp(opt, "push") == 0)
return push;
else if (strcmp(opt, "pop") == 0)
return pop;
else if (strcmp(opt, "inject") == 0)
return inject;
else if (strcmp(opt, "eject") == 0)
return eject;
else if (strcmp(opt, "end") == 0)
return end;
}

void PrintDeque(Deque D)
{
PtrToNode temp;

printf( "Inside deque: " );
temp = D->Front->Next;
while (temp != NULL )
{
printf("%d ", temp->Element);
temp = temp->Next;
}

printf("\n---------\n");
}
