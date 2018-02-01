#include<stdio.h>
#include<stdlib.h>

void Judge_Insertion(int Initial[], int Result[], int N);
void Judge_Heap(int Initial[], int Result[], int N);

int main()
{
	int i, N;
	int Initial1[200], Initial2[200], Result1[200], Result2[200];
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &Initial1[i]);
		Initial2[i] = Initial1[i];
	}
	for (i = 0; i < N; i++)
	{
		scanf("%d", &Result1[i]);
		Result2[i] = Result1[i];
	}
	Judge_Insertion(Initial1, Result1, N);
	Judge_Heap(Initial2, Result2, N);
	return 0;
}
void Judge_Insertion(int Initial[], int Result[], int N)
{
	int i, j, P, temp;
	int flag = 0;
	int Judge[200];
	for (i = 0; i<N; i++)
	{
		Judge[i] = Initial[i];
	}
	for (P = 1; P<N; P++)
	{
		temp = Initial[P];
		for (i = P; i>0 && Initial[i - 1]>temp; i--)
			Initial[i] = Initial[i - 1];
		Initial[i] = temp;
		for (j = 0; j<N; j++)
		{
			if (Result[j] != Initial[j])
			{
				break;
			}
		}
		if (j == N)
		{
			flag = 1;
			break;
		}
	}

	P++;
	if (flag == 1)
	{
		temp = Initial[P];
		for (i = P; i>0 && Initial[i - 1]>temp; i--)
			Initial[i] = Initial[i - 1];
		Initial[i] = temp;
		printf("Insertion Sort\n");
		printf("%d", Initial[0]);
		for (i = 1; i<N; i++)
			printf(" %d", Initial[i]);
	}
	else
		return;
}
void Judge_Heap(int Initial[], int Result[], int N)
{
	void PercDown(int A[], int i, int N);
	int i, j;
	int temp, flag = 0;
	for (i = N / 2; i >= 0; i--)
		PercDown(Initial, i, N);
	for (i = N - 1; i>0; i--)
	{
		temp = Initial[i];
		Initial[i] = Initial[0];
		Initial[0] = temp;
		PercDown(Initial, 0, i);
		for (j = 0; j<N; j++)
		{
			if (Result[j] != Initial[j])
				break;
		}
		if (j == N)
		{
			flag = 1;
			break;
		}
	}

	i--;
	if (flag == 1)
	{
		printf("Heap Sort\n");
		temp = Initial[i];
		Initial[i] = Initial[0];
		Initial[0] = temp;
		PercDown(Initial, 0, i);
		printf("%d", Initial[0]);
		for (i = 1; i<N; i++)
			printf(" %d", Initial[i]);
	}
	else
		return;
}
void PercDown(int A[], int i, int N)
{
	int Child, temp;
	for (temp = A[i]; 2 * i + 1<N; i = Child)
	{
		Child = 2 * i + 1;
		if (Child != N - 1 && A[Child + 1]>A[Child])
			Child++;
		if (temp <A[Child])
			A[i] = A[Child];
		else break;
	}
	A[i] = temp;
}
