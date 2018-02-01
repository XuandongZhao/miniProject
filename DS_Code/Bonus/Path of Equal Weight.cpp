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
  
//�˴���ʹ��ǰ����ɾ����������+�����system("PAUSE")  
//ifstream fin("in.txt");  
//#define cin fin  
  
int weight[101]={0};  
int parent[101]={0};  
int childNum[101]={0};  
int sum[101]={0};  
int linkNode[101][101]={0};  
  
void print(int pa){         //����Ҷ�ڵ���ݴ�ӡ����  
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
  
void DFS(int cur,int s){            //�����������  
    int next;  
    for(int i=0;i<childNum[cur];i++){  
        next = linkNode[cur][i];  
        sum[next] = sum[cur]+weight[next];  
        if(sum[next]==s){               //���Ȩֵ�͵���Ŀ��ֵ  
            if(childNum[next]==0){      //��ǡ����Ҷ�ڵ㣬�����  
                print(next);  
            }else{          //����Ҷ�ڵ㣬������ѭ��  
                continue;  
            }  
        }else if(sum[next]<s){       //Ȩֵ��С��Ŀ�꣬�����������  
            DFS(next,s);  
        }else{                  //Ȩֵ�ʹ���Ŀ�꣬û��Ҫ�������Ѹýڵ�  
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
        sort(linkNode[nonleaf],linkNode[nonleaf]+num,cmp);      //��ÿ���ڵ�������ӽڵ�Ӵ�С����  
    }  
    if(m==0){           //������һ�����ڵ�ʱ  
        if(weight[0]==s)cout<<weight[0]<<endl;  
        return 0;  
    }  
    memcpy(sum,weight,n*sizeof(int));       //����Ȩ�ص�sum����  
    DFS(0,s);  
   // system( "PAUSE");  
    return 0;  
}  
