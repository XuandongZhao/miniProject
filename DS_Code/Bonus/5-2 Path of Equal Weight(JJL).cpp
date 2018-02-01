/*Author:Ji Jialin;	ID:3150104483;	No.02*/

#include<stdio.h>
#include<stdlib.h>
struct TreeNode {
	int ID;
	int Children_num;
	int flag;
	int degree;
	long Weight;
	int* Children;
}Tree[100];

typedef struct Path *P;
struct Path
{
	int ID;
	P Next;
};

typedef struct Path2 *P2;
struct Path2
{
	P First;
	P2 Next;
};

void Search(int ID);
int cmp(const void *a, const void *b);
void sort(int ID);
void Calculate_degree(int ID);
void Print(P2 way2);
int Right_ot_Wrong(P temp_P);

int Node_num, nonleafnode_num;
long long GivenWeight;
P way;
P way_t;
P Rear;
P2 way2;
P2 way_t2;
P2 Rear2;

int main(void)
{
	int i, ID, j;
	P way = (P)malloc(sizeof(struct Path));
	way_t = way;
	Rear = way;
	way2 = (P2)malloc(sizeof(struct Path2));
	way_t2 = way2;
	Rear2 = way2;
	way->Next = NULL;
	way2->Next = NULL;
	way2->First = way;

	scanf("%d%d%lld", &Node_num, &nonleafnode_num, &GivenWeight);

	for (i = 0; i < Node_num; i++)
	{
		scanf("%ld", &(Tree[i].Weight));
		Tree[i].Children = NULL;
		Tree[i].Children_num = 0;
		Tree[i].flag = 0;
	}

	for (i = 1; i <= nonleafnode_num; i++)
	{
		scanf("%d", &ID);
		scanf("%d", &(Tree[ID].Children_num));
		Tree[ID].Children = (int*)malloc(sizeof(int)*Tree[ID].Children_num);
		for (j = 0; j < Tree[ID].Children_num; j++)
			scanf("%d", &(Tree[ID].Children[j]));
	}
	sort(0);
	Calculate_degree(0);
	Search(0);
	Print(way2);

	return 0;
}

void sort(int ID)
{
	if (Tree[ID].Children == NULL) return;
	int i;
	qsort(Tree[ID].Children, Tree[ID].Children_num, sizeof((Tree[ID].Children)[0]), cmp);
	for (i = 0; i < Tree[ID].Children_num; i++)
	{
		sort((Tree[ID].Children)[i]);
	}
}

int cmp(const void *a, const void *b)
{
	return Tree[*(int *)b].Weight > Tree[*(int *)a].Weight ? 1 : -1; //Ωµ–Ú≈≈–Ú
}

void Calculate_degree(int ID)
{
	int i;
	Tree[ID].degree = 0;
	if (Tree[ID].Children_num == 0)
	{
		Tree[ID].degree = 1;
		return;
	}
	else {
		for (i = 0; i<Tree[ID].Children_num; i++)
		{
			Calculate_degree((Tree[ID].Children)[i]);
			Tree[ID].degree += Tree[(Tree[ID].Children)[i]].degree;
		}
	}
}

void Search(int ID)
{
	int i;
	if (Tree[ID].flag<Tree[ID].degree)
	{
		way_t->ID = ID;
		Tree[ID].flag++;

		if (ID<Node_num)
		{
			if (Tree[ID].Children_num == 0)
			{
				Rear2 = (P2)malloc(sizeof(struct Path2));
				way_t2->Next = Rear2;
				Rear2->Next = NULL;
				way_t2 = Rear2;
				way_t = (P)malloc(sizeof(struct Path));
				way_t->Next = NULL;
				way_t2->First = way_t;
				Rear = way_t;
				Search(0);
			}
			else
			{
				Rear = (P)malloc(sizeof(struct Path));
				way_t->Next = Rear;
				Rear->Next = NULL;
				way_t = Rear;
			}
		}
		for (i = 0; i<Tree[ID].Children_num; i++)
		{
			Search((Tree[ID].Children)[i]);
		}
	}
	else return;
}

void Print(P2 way2)
{
	P2 t2 = way2;
	while (t2->Next != NULL)
	{
		P t = t2->First;
		if (Right_ot_Wrong(t) == 1)
		{
			while (t != NULL)
			{
				printf("%ld", Tree[t->ID].Weight);
				if (t->Next != NULL) printf(" ");
				t = t->Next;
			}
			printf("\n");
		}
		t2 = t2->Next;
	}
}

int Right_ot_Wrong(P temp_P)
{
	P Pt = temp_P;
	long long sum = 0;
	while (Pt != NULL)
	{
		sum += Tree[Pt->ID].Weight;
		Pt = Pt->Next;
	}
	if (sum == GivenWeight) return 1;
	else return 0;
}