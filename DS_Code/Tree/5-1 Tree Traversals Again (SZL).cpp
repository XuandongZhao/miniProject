#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TotalNodes 31 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree Build(int N);
void PostOrderTraversal(Tree T);

int main(void)
{
	int N;
	Tree tree;
	
	scanf("%d", &N);
	tree = Build(N);
	PostOrderTraversal(tree);
}
Tree Build(int N)
{
	int i, index;
	Tree pre, root;
	Tree *stack = (Tree *)malloc(sizeof(Tree)*TotalNodes);
	char s[5];
	
	index =  0;
	pre = NULL;
	for(i = 0; i < 2*N; i++)
	{
		scanf("%s", s);
		if(!(strcmp(s, "Push")))
		{
			Tree tree = (Tree)malloc(sizeof(struct TreeNode *));
			scanf("%d", &tree->Element);
			tree->Left = NULL;
			tree->Right = NULL;
			if(pre == NULL && index == 0)
			{
				stack[index++] = tree;
				root = tree;	
			}else if(pre == NULL)
			{
				Tree temp;
				
				temp = stack[index-1];
				temp->Left = tree;
				stack[index++] = tree;
			}else if(pre != NULL)
			{
				pre->Right = tree;
				stack[index++] = tree;
			}
			pre = NULL;
		}else if((!strcmp(s, "Pop")))
		{
			index--;
			pre = stack[index];
		}
	}
	
	return root;
}
void PostOrderTraversal(Tree T)
{
	Tree *stack = (Tree *)malloc(sizeof(Tree)*TotalNodes);
	Tree pre, cur;
	int top = 0, index = 0;
	
	if(T == NULL)
		return;
	pre = NULL;
	stack[++top] = T;
	while(top != 0)
	{
		cur = stack[top];
		if((cur->Left == NULL && cur->Right ==NULL) || 
		(pre != NULL && (pre == cur->Left || pre == cur->Right)))
		{
			if(index == 0)
				printf("%d", cur->Element);
			else
				printf(" %d", cur->Element);
			index++;
			top--;
			pre = cur;
		}else{
		
			if(cur->Right != NULL)
				stack[++top] = cur->Right;
			if(cur->Left != NULL)
				stack[++top] = cur->Left;
		}
	}
	
}