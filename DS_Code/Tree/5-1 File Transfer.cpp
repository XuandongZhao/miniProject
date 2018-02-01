#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef int* SetType;

void Union(SetType S, int Root1,int Root2)
{ 
	if(S[Root1]<S[Root2]) 
	S[Root2] = Root1;
	else 
	S[Root1] = Root2;
}
/*int Find( int* S,ElementType X)
{
	ElementType root, trail, lead;
	for (root = X; S[root] > 0; root = S[root]);
	for (trail = X; trail != root; trail = lead)
	{
		lead = S[trail];
		S[trail] = root;
	}
	return root;
}*/
int Find(SetType S, ElementType X)
{ /* 默认集合元素全部初始化为-1 */
	for (; S[X] >= 0; X = S[X]);
	S[X]--;
	return X;
}

void Input_connection(SetType S)
{
	ElementType u, v;
	int Root1, Root2;
	scanf("%d %d\n", &u, &v);
	Root1 = Find(S, u - 1);
	Root2 = Find(S, v - 1);
	if (Root1 != Root2)
		Union(S, Root1, Root2);
}

void Check_connection(SetType S)
{
	ElementType u, v;
	int Root1, Root2;
	scanf("%d %d\n", &u, &v);
	Root1 = Find(S, u - 1);
	Root2 = Find(S, v - 1);
	if (Root1 == Root2)
		printf("yes\n");
	else printf("no\n");
}

void Check_network(SetType S, int n)
{
	int i, counter = 0;
	for (i = 0; i<n; i++) 
	{
		if (S[i] < 0) counter++;
	}
	if (counter == 1)
		printf("The network is connected.\n");
	else
		printf("There are %d components.\n", counter);
}

int main()
{
	int N,i;
	char c;
	SetType S;

	scanf("%d", &N);
	S = (int*)malloc(sizeof(int)*N);	
	for (i = 0; i < N; i++)
		S[i] = -1;
	do 	{
		scanf("%c", &c);
		switch (c)
		{
		case 'I': Input_connection(S); break;
		case 'C': Check_connection(S); break;
		case 'S': Check_network(S, N); break;
		}
	} while (c != 'S');
	return 0;
}