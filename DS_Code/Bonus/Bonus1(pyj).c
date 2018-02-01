#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
    int ID;
    int n_child;
    int weight;
    int sum; /*把sum信息保存在节点中*/
    Tree parent;
    Tree * child;
    int flag;/*看有没有出现过*/
};
Tree NodeArray[101];/*用一个数组来放置各节点，数组下标即nodeID*/
int find(int N, Tree* NodeArray)
{
    if(NodeArray[N] == NULL)
        return 0;
    if(NodeArray[N] -> flag ==1)
        return 1;
    else return 0;
}
void sort(Tree parent)
{
    Tree temp;
    int nchild = parent -> n_child;
    int i,j;
    temp = (Tree) malloc( sizeof(struct TreeNode));
    for(i = 0; i< nchild-1; i++)
        for(j = 0; j < nchild-i-1; j++)
        {
            if(parent->child[j]-> weight < parent->child[j+1]-> weight)
            {
                temp = parent->child[j];
                parent->child[j] = parent->child[j+1];
                parent->child[j+1] = temp;
            }
        }
    
}
int pathweight[101][101];
int nth = 0;
void path(int parent, int S)
{
    int i,j;
    NodeArray[parent] -> sum += NodeArray[parent] -> parent ->sum;
    if(NodeArray [parent] ->sum== S)
    {
        if(NodeArray[parent] ->n_child  == 0)/*到达叶节点*/
        {
            j =0;
            Tree p = NodeArray[parent];
            do{
                pathweight[nth][j] = p -> weight;
                p = p -> parent;
                j++;
            }while(p ->ID != -1);/*从根节点到叶节点打印*/
            for(j--;j>0;j--)
            {
                printf("%d ", pathweight[nth][j]);
            }
            printf("%d", pathweight[nth][j]);
            printf("\n");
            nth++;/*下一条可能路径编号*/
            return;
        }
        else /*在sum == S但不是叶节点*/
        {
            nth++;
            return;
        }
    }
    else if(NodeArray[parent] ->sum > S)
    {
        nth++;
        return;
    }
    else if((NodeArray[parent] -> sum <S) &&(NodeArray[parent] ->n_child  == 0))
    {
            nth++;
            return;
    }

    for (i = 0; i< NodeArray[parent] -> n_child; i++)
    {
        path( (NodeArray[parent]) -> child[i]-> ID,S);/*DFS*/
    }
    
}

int main(void)
{
    int N, M, S, parentID, n_child;
    int i, j, k;
    int weight[101];
    Tree parent;
    Tree head;
    head = (Tree) malloc( sizeof(struct TreeNode));
    head -> ID = -1;
    head -> parent = NULL;
    head -> n_child = 1;
    scanf("%d %d %d",&N, &M, &S);
    if(N == 0) /*如果节点数为0*/
        return 0;
    for (i = 0; i< N; i++)
        scanf("%d",& weight[i]);
    if (M == 0)/*如果节点数为1*/
    {
        if (weight [0] == S)
            printf("%d\n",S);
        return 0;
    }
    for (i = 0; i < M; i++)
    {
        scanf("%d %d",&parentID, &n_child);
        if(find(parentID, NodeArray))/*看这个ID之前是不是作为某一个parent节点的child出现过*/
        {
            parent = NodeArray[parentID];
            parent -> n_child = n_child;
            parent ->child = (Tree*)malloc (parent->n_child *sizeof(Tree));
        }
        else
        {
            parent = (Tree) malloc( sizeof(struct TreeNode));
            parent -> n_child = n_child;
            parent -> ID = parentID;
            parent -> sum = parent -> weight = weight[parentID];
            parent -> flag = 1;
            parent ->child = (Tree*)malloc (n_child *sizeof(Tree));
            NodeArray[parentID] = parent;
        }
        if(parentID == 0)
        {
            head -> child = &parent;
            head -> n_child = 1;
            head ->weight = head -> sum = 0;
            parent -> parent = head;
            head -> ID =-1;
        }
        k = 0;
        for(j = 0; j< n_child; j++) /*创建父节点的n_child个子节点*/
        {
            int childID;
            scanf("%d", &childID);
            if(!find(childID,NodeArray))
            {
                Tree child;
                child = (Tree) malloc( sizeof(struct TreeNode));
                child -> n_child = 0;
                child -> child = NULL;
                child -> ID = childID;
                child -> parent = parent;
                child -> sum = child -> weight = weight[childID];
                child -> flag = 1;
                parent -> child[j] = child;
                NodeArray[childID]= child;
            }
            else{
                parent -> child[j] = NodeArray[childID];
                NodeArray[childID] -> parent = parent;
            }
        }
        sort(parent);/*根据weight从大到小重新对子节点排序,简化输出时的操作*/
    }
        path(0, S);
}