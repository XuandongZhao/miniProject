#include<stdio.h>
#include<stdlib.h>
#define MAX 30 
void getpre(int *Post, int *In, int root);
int main()
{
	int N, i;
	scanf("%d", &N);
	int Post[MAX], Pre[MAX], In[MAX];
	for (i = 0; i < N; i++)
		scanf("%d", &Post[i]);
	for (i = 0; i < N; i++)
		scanf("%d", &In[i]);
	printf("Preorder:");
	getpre(Post, In, N);
	printf("\n");
	return 0;
}
void getpre(int *Post, int *In, int root)
{
	if (root <= 0)
		return;
	int n = Post[root - 1];
	int i;
	for (i = 0; i < root; i++)
	{
		if (In[i] == n)
			break;
	}
	printf(" %d", n);
	getpre(Post, In, i);
	getpre(Post + i, In + i + 1, root - i - 1);
}