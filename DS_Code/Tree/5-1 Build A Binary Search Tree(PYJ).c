/*题目要求建立一棵给定结构的二叉搜索树，并且进行层序遍历。
 因为给定了结构，因此不能采用一般的方法来创建这棵树，
 题目指定了采用数组存储，数组存储树的一个问题在于不容易判断树是不是空，
 以前使用链表存储树的时候，可以通过结点是否为NULL来判断，
 这里给出一种简单易行的办法。
 【数组存储树的方法】
 首先建立一个比树的结点个数多1的数组TempT，
 0位置存储数据-1，然后让树T从位置1开始存储，
 这样，让空树的索引为-1，当访问T[-1]的时候。
 实际访问的是TempT[0]，而这里存储的数据正好是-1.
 因此可以通过这样来防止地址越界和方便的的处理。
 【元素插入的处理】
 因为二叉搜索树的中序遍历是所有元素的升序，因此将要插入的所有元素进行排序，
 即可得到树的中序遍历结果。
 观察数组索引的增加，是根、左、右的顺序进行的，也就是树的先序遍历，
 对于二叉搜索树，左侧的元素一定小于右侧，
 因此只需要设计一个计算左子树和右子树元素个数的函数，
 然后在中序遍历序列中截取，例如第一次截取，0位置的元素左侧有5个元素，
 则第6个就是根，后面的就是右子树，然后递归的解决所有子树，完成插入。
 【元素的层序遍历问题】
 层序遍历和DFS基本是一样的，只需要一个队列，然后进行先序遍历即可。*/

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode{
    int element;
    int left;
    int right;
};

void sort(int keys[],int N)
{
    int i,j = 0;
    int temp;
    for( j = 0; j < N; j++)
        for(i = 0;i < N-j-1; i++)
        {
           if(keys[i]>keys[i+1])
            {
                temp = keys[i+1];
                keys[i+1] = keys[i];
                keys [i] = temp;
            }
        }
}
int j = 0;
void keysput (Tree Tarray[],int index, int* keys)
{
    if(index != -1)
    {
        keysput(Tarray, Tarray[index] -> left,keys);
        Tarray[index] -> element = keys[j];
        j++;
        keysput(Tarray, Tarray[index] -> right, keys);
    }
}
int k= 0;
void levelorder(Tree Tarray[],int index, int N)
{
    struct TreeNode * Queue[101], *p;
    int front, rear;
    front = rear = 0;
    if(index != -1)
    {
        Queue[rear] = Tarray[index];
        rear++;
        while(front != rear)
        {
            p = Queue[front];
            front++;
            if(front< N) printf("%d ",p-> element);
            else printf("%d",p-> element);
            if(p-> left !=-1){
                Queue[rear]=Tarray[p -> left];
                rear++;
            }
            if(p-> right != -1){
                Queue[rear]=Tarray[p -> right];
                rear++;
            }
        }
    }
}
void indexput(Tree Tarray[], int index)
{
    Tree T;
    int lindex,rindex;
    T = (Tree) malloc(sizeof(struct TreeNode));
    if(index == -1) return;
    else{
        Tarray[index] = T;
        scanf("%d %d",&lindex, &rindex);
        T -> left = lindex;
        T -> right = rindex;
    }
    indexput(Tarray, lindex);
    indexput(Tarray, rindex);
}
int main(void)
{
    Tree Tarray[150];
    int N,i;
    int key;
    int keys[150];
    scanf("%d", &N);
    if(N == 0) return 0;
    else if(N == 1)
    {
        scanf("%d",&key);
        printf("%d",key);
    }
    else
    {
        indexput(Tarray, 0);
        for(i = 0; i < N ; i++)
        {
            scanf("%d", &keys[i]);
        }
        sort(keys, N);
        keysput(Tarray, 0, keys);
        levelorder(Tarray ,0, N);
    }
}