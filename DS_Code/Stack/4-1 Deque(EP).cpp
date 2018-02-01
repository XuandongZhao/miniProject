Deque CreateDeque(){
Deque D;
PtrToNode head;

head = malloc( sizeof( struct Node ) );
D = malloc( sizeof( struct DequeRecord ) );
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

p = malloc( sizeof( struct Node ) );
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

p = malloc( sizeof( struct Node ) );
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
scanf_s("%s", opt, 7);
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
