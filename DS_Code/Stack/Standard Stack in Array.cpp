//Realize Stack in Array
//Xuandong Zhao

#ifndef _Stack_h

struct StackRecord;
typedef struct StackRecord *Stack;
typedef int ElementType;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void Push(ElementType X,Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

#endif // !Stack_h

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

int IsEmpty(Stack S)
{
	return S->TopOfStack == 0;
}

int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack(int MaxElements)
{
	Stack S;
	S = (Stack)malloc(sizeof(struct StackRecord));
	S->Array = (ElementType*)malloc(sizeof(ElementType)*MaxElements);
	S->Capacity = MaxElements;
	MakeEmpty(S);
	return S;
}

void DisposeStack(Stack S)
{
	if (S != NULL)
	{
		free(S->Array);
		free(S);
	}
}

void MakeEmpty(Stack S)
{
	return S->TopOfStack == 0;
}

void Push(ElementType X, Stack S)
{
	if(!IsFull(S))
		S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S)
{
	if (!IsEmpty(S))
		return S->Array[S->TopOfStack];
}

void Pop(Stack S)
{
	if (!IsEmpty(S))
		S->TopOfStack--;
}

ElementType TopAndPop(Stack S)
{
	if (!IsEmpty(S))
		return S->Array[S->TopOfStack--];
	else
		return 0;
}
