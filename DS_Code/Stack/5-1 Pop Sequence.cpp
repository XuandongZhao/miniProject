#include<stdio.h>
#include<stdlib.h>
int pop(int *P);
void push(int *P);
int top(int *p);

int main()
{
	int num, space, N;
	int i, j, k;
	int t = 0;
	scanf("%d%d%d", &num, &space, &N);
	int *P;
	P = (int*)malloc(sizeof(int)*space);
	int *Q;
	Q = (int*)malloc(sizeof(int)*num);
	while (N--) 
	{
		for (i = 0; i < space; i++)
		{
			scanf("%d", P[i]);
		}
		for (i = 0; i < space; i++)
		{
			if(Q[k]!=Q)
			for (k = 0; k < P[i]; k++)
			{
				Q[k] = m++;
			}
		}
	}
}