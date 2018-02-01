/* ���Ա�����ʵ�֣����������������������������������������������������������������������������������������������������������������������������������������������� */
typedef int Position;
typedef struct LNode *List;
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last;
};

/* ��ʼ�� */
List MakeEmpty()
{
	List L;

	L = (List)malloc(sizeof(struct LNode));
	L->Last = -1;

	return L;
}

/* ���� */
#define ERROR -1

Position Find(List L, ElementType X)
{
	Position i = 0;

	while (i <= L->Last && L->Data[i] != X)
		i++;
	if (i > L->Last)  return ERROR; /* ���û�ҵ������ش�����Ϣ */
	else  return i;  /* �ҵ��󷵻ص��Ǵ洢λ�� */
}

/* ���� */
/*ע��:�ڲ���λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P�Ǵ洢�±�λ�ã���0��ʼ�������߲�1*/
bool Insert(List L, ElementType X, Position P)
{ /* ��L��ָ��λ��Pǰ����һ����Ԫ��X */
	Position i;

	if (L->Last == MAXSIZE - 1) {
		/* ��ռ����������ܲ��� */
		printf("����");
		return false;
	}
	if (P<0 || P>L->Last + 1) { /* ������λ�õĺϷ��� */
		printf("λ�ò��Ϸ�");
		return false;
	}
	for (i = L->Last; i >= P; i--)
		L->Data[i + 1] = L->Data[i]; /* ��λ��P���Ժ��Ԫ��˳������ƶ� */
	L->Data[P] = X;  /* ��Ԫ�ز��� */
	L->Last++;       /* Last��ָ�����Ԫ�� */
	return true;
}

/* ɾ�� */
/*ע��:��ɾ��λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P�Ǵ洢�±�λ�ã���0��ʼ�������߲�1*/
bool Delete(List L, Position P)
{ /* ��L��ɾ��ָ��λ��P��Ԫ�� */
	Position i;

	if (P<0 || P>L->Last) { /* ���ձ�ɾ��λ�õĺϷ��� */
		printf("λ��%d������Ԫ��", P);
		return false;
	}
	for (i = P + 1; i <= L->Last; i++)
		L->Data[i - 1] = L->Data[i]; /* ��λ��P+1���Ժ��Ԫ��˳����ǰ�ƶ� */
	L->Last--; /* Last��ָ�����Ԫ�� */
	return true;
}

/*����ָ������--------------------------------------------------------*/

typedef struct LNode *PtrToLNode;
struct LNode {
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

/* ���� */
#define ERROR NULL

Position Find(List L, ElementType X)
{
	Position p = L; /* pָ��L�ĵ�1����� */

	while (p && p->Data != X)
		p = p->Next;

	/* ������������ return p; �滻 */
	if (p)
		return p;
	else
		return ERROR;
}

/* ��ͷ���Ĳ��� */
/*ע��:�ڲ���λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P��������ָ�룬��P֮ǰ�����½�� */
bool Insert(List L, ElementType X, Position P)
{ /* ����Ĭ��L��ͷ��� */
	Position tmp, pre;

	/* ����P��ǰһ����� */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL) { /* P��ָ�Ľ�㲻��L�� */
		printf("����λ�ò�������\n");
		return false;
	}
	else { /* �ҵ���P��ǰһ�����pre */
		   /* ��Pǰ�����½�� */
		tmp = (Position)malloc(sizeof(struct LNode)); /* ���롢��װ��� */
		tmp->Data = X;
		tmp->Next = P;
		pre->Next = tmp;
		return true;
	}
}

/* ��ͷ����ɾ�� */
/*ע��:��ɾ��λ�ò���P����γ���Ƶ������ͬ���γ���Ƶ��i������λ�򣨴�1��ʼ��������P����ɾ�����ָ�� */
bool Delete(List L, Position P)
{ /* ����Ĭ��L��ͷ��� */
	Position tmp, pre;

	/* ����P��ǰһ����� */
	for (pre = L; pre&&pre->Next != P; pre = pre->Next);
	if (pre == NULL || P == NULL) { /* P��ָ�Ľ�㲻��L�� */
		printf("ɾ��λ�ò�������\n");
		return false;
	}
	else { /* �ҵ���P��ǰһ�����pre */
		   /* ��Pλ�õĽ��ɾ�� */
		pre->Next = P->Next;
		free(P);
		return true;
	}
}

//��ջ����----------------------------------------------------------------------
typedef int Position;
struct SNode {
	ElementType *Data; /* �洢Ԫ�ص����� */
	Position Top;      /* ջ��ָ�� */
	int MaxSize;       /* ��ջ������� */
};
typedef struct SNode *Stack;

Stack CreateStack(int MaxSize)
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}

bool IsFull(Stack S)
{
	return (S->Top == S->MaxSize - 1);
}

bool Push(Stack S, ElementType X)
{
	if (IsFull(S)) {
		printf("��ջ��");
		return false;
	}
	else {
		S->Data[++(S->Top)] = X;
		return true;
	}
}

bool IsEmpty(Stack S)
{
	return (S->Top == -1);
}

ElementType Pop(Stack S)
{
	if (IsEmpty(S)) {
		printf("��ջ��");
		return ERROR; /* ERROR��ElementType������ֵ����־���� */
	}
	else
		return (S->Data[(S->Top)--]);
}

//��ջ������-----------------------------------------------------
typedef struct SNode *PtrToSNode;
struct SNode {
	ElementType Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack()
{ /* ����һ����ջ��ͷ��㣬���ظý��ָ�� */
	Stack S;

	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}

bool IsEmpty(Stack S)
{ /* �ж϶�ջS�Ƿ�Ϊ�գ����Ƿ���true�����򷵻�false */
	return (S->Next == NULL);
}

bool Push(Stack S, ElementType X)
{ /* ��Ԫ��Xѹ���ջS */
	PtrToSNode TmpCell;

	TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	TmpCell->Data = X;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
	return true;
}

ElementType Pop(Stack S)
{ /* ɾ�������ض�ջS��ջ��Ԫ�� */
	PtrToSNode FirstCell;
	ElementType TopElem;

	if (IsEmpty(S)) {
		printf("��ջ��");
		return ERROR;
	}
	else {
		FirstCell = S->Next;
		TopElem = FirstCell->Data;
		S->Next = FirstCell->Next;
		free(FirstCell);
		return TopElem;
	}
}


//���С�������������������������������������������������������������������������������������������������������������������������������������������������������������������
typedef int Position;
struct QNode {
	ElementType *Data;     /* �洢Ԫ�ص����� */
	Position Front, Rear;  /* ���е�ͷ��βָ�� */
	int MaxSize;           /* ����������� */
};
typedef struct QNode *Queue;

Queue CreateQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

bool IsFull(Queue Q)
{
	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

bool AddQ(Queue Q, ElementType X)
{
	if (IsFull(Q)) {
		printf("������");
		return false;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return true;
	}
}

bool IsEmpty(Queue Q)
{
	return (Q->Front == Q->Rear);
}

ElementType DeleteQ(Queue Q)
{
	if (IsEmpty(Q)) {
		printf("���п�");
		return ERROR;
	}
	else {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return  Q->Data[Q->Front];
	}
}
//��������-------------------------------------------------------------------------------
typedef struct Node *PtrToNode;
struct Node { /* �����еĽ�� */
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode {
	Position Front, Rear;  /* ���е�ͷ��βָ�� */
	int MaxSize;           /* ����������� */
};
typedef struct QNode *Queue;

bool IsEmpty(Queue Q)
{
	return (Q->Front == NULL);
}

ElementType DeleteQ(Queue Q)
{
	Position FrontCell;
	ElementType FrontElem;

	if (IsEmpty(Q)) {
		printf("���п�");
		return ERROR;
	}
	else {
		FrontCell = Q->Front;
		if (Q->Front == Q->Rear) /* ������ֻ��һ��Ԫ�� */
			Q->Front = Q->Rear = NULL; /* ɾ���������Ϊ�� */
		else
			Q->Front = Q->Front->Next;
		FrontElem = FrontCell->Data;

		free(FrontCell);  /* �ͷű�ɾ�����ռ�  */
		return  FrontElem;
	}
}

