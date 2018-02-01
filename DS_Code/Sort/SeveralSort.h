//sort例程
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void InsertionSort(int A[],int N);
void ShellSort(int A[],int N);
void HeapSort(int A[],int N); 
int main()
{
	int A[MAX] = {0};
	int i,N;
	scanf("%d",&N);
	for(i = 0;i<N;i++)
	{
		scanf("%d",&A[i]);
	}
	HeapSort(A,N);
	for(i = 0;i<N;i++)
	{
		printf("%d ",A[i]);
	}
	return 0;
}

void InsertionSort(int A[],int N)
{
	int i,j;
	int temp;
	for(i = 1;i<N;i++)
	{
		temp = A[i];
		for(j = i;j>0&&A[j-1]>temp;j--)
		{
			A[j] = A[j-1];
		}
		A[j] = temp;
	}
}

void ShellSort(int A[],int N)
{
	int i,j,Increment;
	int temp;
	for(Increment = N/2;Increment>0;Increment/=2)
		for(i = Increment;i<N;i++)
		{
			temp = A[i];
			for(j = i;j>=Increment&&temp<A[j-Increment];j-=Increment)
			{
				A[j] = A[j-Increment];
			}
			A[j] = temp;
		}
}

void HeapSort(int A[],int N)
{
	int i,temp;
	void PerDown(int A[],int i,int N);
	for(i = N/2;i>=0;i--)
		PerDown(A,i,N);
	for(i = N-1;i>0;i--)
	{
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		PerDown(A,0,i);
	}
}
void PerDown(int A[],int i,int N)
{
	int child;
	int temp;
	for(temp = A[i];i*2+1<N;i = child)
	{
		child = i*2+1;
		if(A[child+1]>A[child]&&child < N-1)
			child ++;
		if(temp<A[child])
			A[i] = A[child];
		else 
			break;
	}
	A[i] = temp;
}
