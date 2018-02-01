/*
主要考察了最小生成树的相关知识；
（我采用了Kruskal算法；）
本题测试点的最后两个对于大数据的测试，时间，空间要求比较严格；
自己开始的几个写法都是最后两个点不能过；
于是更改了多次算法；
对于段错误：路径数组一定要开够；
对于超时：个人认为时间主要损耗在于：1.对联通集find时若不路径压缩，可能会超时
2.每次找最少的cost时，如果都遍历找最小的话，会超时
于是最后更改写法为：
输入cost和state时就对其经行排序（利用快排）；
在findmin（）时直接取最左端的那一个（如果被占领则跳过，优先选取state=1的路径）；
同时还要注意到，可能存在无法修复的情况，此时应直接赋一个最大cost给该站点；
*/


#include<stdio.h>
#include<stdlib.h>
int M, N;//记录city和highway总数
int city1, city2;
int count1, count2;
int p1 = 0, p2 = 0;//记录state=1和state=0的highway数量


struct v {
	int c1;
	int c2;
	int cost;
} cost1[250000], cost2[250000];//分别记录state=1和state=0的路径


int DisjSet[520];//联通集
int costp[520] = { -1 };
int Kruskal(int city);
int find(int city);
int findmin(int conquer);
void output();


int cmp1(const void *a, const void *b)
{
	return ((struct v*)a)->cost - ((struct v*)b)->cost;
} //快排比较函数


int main(void)
{
	int i = 0, j = 0;
	int c1, c2;
	int cost = 0, state = 0;
	scanf("%d%d", &M, &N);
	for (i = 0; i<N; i++) {
		scanf("%d%d%d%d", &c1, &c2, &cost, &state);
		if (state == 1) {
			cost1[p1].c1 = c1;
			cost1[p1].c2 = c2;
			cost1[p1].cost = cost;
			p1++;
		}//如果state=1，记录于cost1
		else {
			cost2[p2].c1 = c1;
			cost2[p2].c2 = c2;
			cost2[p2].cost = cost;
			p2++;
		}//如果state=0,记录于cost2
	}
	qsort(cost1, p1, sizeof(struct v), cmp1);
	qsort(cost2, p2, sizeof(struct v), cmp1);//对cost1和cost2经行快排
	p1--;
	p2--;
	for (i = 1; i <= M; i++) {
		count1 = count2 = 0;
		city1 = city2 = 0;
		for (j = 1; j <= M; j++)
			DisjSet[j] = 0;
		costp[i] = Kruskal(i);//遍历所有city,找到每个city的cost
	}
	output();//输出函数
	return 0;
}
int Kruskal(int city)
{
	int V, W;
	int costs = 0;
	int edge = 0;
	int min;
	for (;;) {
		if (edge == M - 2)
			break;//如果联通，break；
		city1 = city2 = 0;
		min = findmin(city);//找到最小cost的路径
		if (min == 0x7FFFFFFF) {
			return min;
		}//无法修复的情况
		V = find(city1);
		W = find(city2);//找到两个点的根节点（判断两个city是否已联通
		if (V != W) {
			edge++;
			if (min>0) {
				costs = costs + min;//如果需要修复，更改costs
			}
			DisjSet[W] = V;//联通
		}
	}
	return costs;
}
int findmin(int conquer)
{
	int i = 0;


	int min = 0x7FFFFFFF;
	//优先考虑state=1的highway；
	while (cost1[count1].c1 == conquer || cost1[count1].c2 == conquer) {
		count1++;
	}//如果被攻占，不考虑，剔除；
	if (count1 <= p1) {
		city1 = cost1[count1].c1;
		city2 = cost1[count1].c2;
		min = cost1[count1].cost;
		count1++;//将已选择的点剔除
		return -1 * min;
	}
	else {
		//若为联通，再考虑state=0的highway
		while (cost2[count2].c1 == conquer || cost2[count2].c2 == conquer) {
			count2++;
		}
		//若被攻占，不考虑，剔除
		if (count2 <= p2) {
			city1 = cost2[count2].c1;
			city2 = cost2[count2].c2;
			min = cost2[count2].cost;
			count2++;//将已选择的点剔除
			return min;
		}
	}
	//若还是未联通泽表明无法修复，返回一个大值
	return min;


}


int find(int city)
{
	if (DisjSet[city] <= 0)
		return city;//找到根节点返回
	else
		return DisjSet[city] = find(DisjSet[city]);//路径压缩
}


void output()
{
	int max = 0;
	int i = 0;
	int flag = 1;
	for (i = 1; i <= M; i++) {
		if (costp[i]>max)
			max = costp[i];
	}//找到最大cost
	if (max == 0)
		printf("0");//若不需修复，输出0
	else
		for (i = 1; i <= M; i++) {
			if (costp[i] == max) {
				if (flag) {
					printf("%d", i);
					flag = 0;
				}
				else
					printf(" %d", i);

			}
		}
}