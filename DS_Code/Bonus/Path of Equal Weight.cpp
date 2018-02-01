#include <iostream>  
#include <fstream>  
#include <algorithm>  
#include <stack>  
#include <vector>  
#include <queue>  
#include <cstdio>  
#include <cstring>  
#include <memory>  
using namespace std;  
  
//此代码使用前，需删除下面两行+后面的system("PAUSE")  
//ifstream fin("in.txt");  
//#define cin fin  
  
int weight[101]={0};  
int parent[101]={0};  
int childNum[101]={0};  
int sum[101]={0};  
int linkNode[101][101]={0};  
  
void print(int pa){         //根据叶节点回溯打印链表  
    stack<int> st;  
    while(pa != -1){  
        st.push(weight[pa]);  
        pa = parent[pa];  
    }  
    cout<<st.top();  
    st.pop();  
    while(!st.empty()){  
        cout<<' '<<st.top();  
        st.pop();             
    }  
    cout<<endl;  
}  
  
void DFS(int cur,int s){            //深度优先搜索  
    int next;  
    for(int i=0;i<childNum[cur];i++){  
        next = linkNode[cur][i];  
        sum[next] = sum[cur]+weight[next];  
        if(sum[next]==s){               //如果权值和等于目标值  
            if(childNum[next]==0){      //又恰好是叶节点，则输出  
                print(next);  
            }else{          //不是叶节点，则跳出循环  
                continue;  
            }  
        }else if(sum[next]<s){       //权值和小于目标，继续深度搜索  
            DFS(next,s);  
        }else{                  //权值和大于目标，没必要继续深搜该节点  
            continue;  
        }  
  
    }  
}  
  
bool cmp(const int& aa,const int& bb){  
    return weight[aa] > weight[bb];  
}  
  
int main()  
{  
    int n,m,s;  
    scanf("%d %d %d",&n,&m,&s);  
    int i,j;  
    for(i=0;i<n;i++)scanf("%d",&weight[i]);  
    int nonleaf,num,leaf;  
    parent[0] = -1;  
    for(i=0;i<m;i++){  
        scanf("%d %d",&nonleaf,&num);  
        childNum[nonleaf] = num;  
        for(j=0;j<num;j++){  
            scanf("%d",&leaf);  
            linkNode[nonleaf][j] = leaf;  
            parent[leaf]=nonleaf;  
        }  
        sort(linkNode[nonleaf],linkNode[nonleaf]+num,cmp);      //把每个节点的所有子节点从大到小排序  
    }  
    if(m==0){           //当仅有一个根节点时  
        if(weight[0]==s)cout<<weight[0]<<endl;  
        return 0;  
    }  
    memcpy(sum,weight,n*sizeof(int));       //拷贝权重到sum数组  
    DFS(0,s);  
   // system( "PAUSE");  
    return 0;  
}  
