#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 300000
#define Infinity 10000000
/*这算法100ms就够了，哪里用的着800ms，这还是Top Level的题么……

暂时懒的写思路……零基础学习Verilog和VGA中……有空会补上……
看代码应该能看懂吧orz……其实就是Prim加并查集（记得用size优化），
用Prim时记得计数连通分部的数量，除被攻占城市外连通分部的数量变为1时就不用再加边了
（这是重点，可以减少很多很多时间），库函数的快排qsort肯定比你自己写的快，
memset也比你for循环赋值快，C语言标准库很强大的，减少函数调用，函数调用很浪费时间的，
没事调用那么多函数干嘛，一个main就够了啊，综上所述，100ms就够了*/
struct Edge{
    int u;
    int v;
    int weight;
    int status;
};

int comp(const void *a, const void *b){
    struct Edge *pa = (struct Edge*)a;
    struct Edge *pb = (struct Edge*)b;
    
    if(pa->status != pb->status){
        return pb->status - pa->status;
    }
    return pa->weight - pb->weight;
}

int main() 
{
    struct Edge E[MAX];
    int N, M, i, j, max = 0, connect, index, fu, fv, tmp, flag = 1, cost[MAX], UF[MAX];
    
    scanf("%d%d", &N, &M);
    for(i = 0; i < M; i++)
	{
        scanf("%d%d%d%d", &E[i].u, &E[i].v, &E[i].weight, &E[i].status);
    }
    qsort(E, M, sizeof(E[0]), comp);
    memset(cost, 0, sizeof(int) * (N + 1));
    
    for(i = 1; i <= N; i++){
        connect = 1;
        memset(UF, -1, sizeof(int) * (N + 1));
        for(j = 0; j < M; j++){
            if(E[j].u != i&&E[j].v != i){
                index = fu = E[j].u;
                while(UF[fu] >= 0){
                    fu = UF[fu];
                }
                while(index != fu){
                    tmp = UF[index];
                    UF[index] = fu;
                    index = tmp;
                }
                
                index = fv = E[j].v;
                while(UF[fv] >= 0){
                    fv = UF[fv];
                }
                while(index != fv){
                    tmp = UF[index];
                    UF[index] = fv;
                    index = tmp;
                }
                
                if(fu != fv){
                    if(fu <= fv){
                        UF[fu] += UF[fv];
                        UF[fv] = fu;
                    }
                    else{
                        UF[fv] += UF[fu];
                        UF[fu] = fv;
                    }
                    
                    connect++;
                    if(0 == E[j].status){
                        cost[i] += E[j].weight;
                    }
                    if(connect == N - 1)
                        break;
                }
            }
        }
        if(connect != N - 1){
            cost[i] = Infinity;
        }
        if(cost[i] > max){
            max = cost[i];
        }
    }
    
    if(0 != max){
        for(i = 1; i <= N; i++){
            if(max == cost[i]){
                if(1 == flag){
                    printf("%d", i);
                    flag = 0;
                }
                else{
                    printf(" %d", i);
                }
            }
        }
    }
    else{
        printf("0");
    }
}