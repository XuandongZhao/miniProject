//Realize Stack Function in List
//Xuandong Zhao
#ifndef_Stack_h
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType 

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif 
struct Node 
{
	ElementType Element;
	PtrToNode Next;
};

int IsEmpty(Stack S)
{
	return S->Next == NULL;
}

Stack CreateStack(Stack S)
{
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	S->Next = NULL;
	return S;
}

void MakeEmpty(Stack S)
{
	while (!IsEmpty(S))
		Pop(S);
}

void Push(ElementType X, Stack S)
{
	Stack Temp;
	Temp = (Stack)malloc(sizeof(struct Node));
	Temp->Element = X;
	Temp->Next = S->Next;
	S->Next = Temp;
}

ElementType Top(Stack S)
{
	if (!IsEmpty(S))
		return S->Next->Element;
	else
		return 0;
}

void Pop(Stack S)
{
	Stack Temp;
	Temp = S->Next;
	printf("%d", Temp->Element);
	S->Next = S->Next->Next;
	free(Temp);
}
