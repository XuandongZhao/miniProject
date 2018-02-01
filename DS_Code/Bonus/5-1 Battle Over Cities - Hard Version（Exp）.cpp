/*
��Ҫ��������С�����������֪ʶ��
���Ҳ�����Kruskal�㷨����
������Ե������������ڴ����ݵĲ��ԣ�ʱ�䣬�ռ�Ҫ��Ƚ��ϸ�
�Լ���ʼ�ļ���д��������������㲻�ܹ���
���Ǹ����˶���㷨��
���ڶδ���·������һ��Ҫ������
���ڳ�ʱ��������Ϊʱ����Ҫ������ڣ�1.����ͨ��findʱ����·��ѹ�������ܻᳬʱ
2.ÿ�������ٵ�costʱ���������������С�Ļ����ᳬʱ
����������д��Ϊ��
����cost��stateʱ�Ͷ��侭���������ÿ��ţ���
��findmin����ʱֱ��ȡ����˵���һ���������ռ��������������ѡȡstate=1��·������
ͬʱ��Ҫע�⵽�����ܴ����޷��޸����������ʱӦֱ�Ӹ�һ�����cost����վ�㣻
*/


#include<stdio.h>
#include<stdlib.h>
int M, N;//��¼city��highway����
int city1, city2;
int count1, count2;
int p1 = 0, p2 = 0;//��¼state=1��state=0��highway����


struct v {
	int c1;
	int c2;
	int cost;
} cost1[250000], cost2[250000];//�ֱ��¼state=1��state=0��·��


int DisjSet[520];//��ͨ��
int costp[520] = { -1 };
int Kruskal(int city);
int find(int city);
int findmin(int conquer);
void output();


int cmp1(const void *a, const void *b)
{
	return ((struct v*)a)->cost - ((struct v*)b)->cost;
} //���űȽϺ���


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
		}//���state=1����¼��cost1
		else {
			cost2[p2].c1 = c1;
			cost2[p2].c2 = c2;
			cost2[p2].cost = cost;
			p2++;
		}//���state=0,��¼��cost2
	}
	qsort(cost1, p1, sizeof(struct v), cmp1);
	qsort(cost2, p2, sizeof(struct v), cmp1);//��cost1��cost2���п���
	p1--;
	p2--;
	for (i = 1; i <= M; i++) {
		count1 = count2 = 0;
		city1 = city2 = 0;
		for (j = 1; j <= M; j++)
			DisjSet[j] = 0;
		costp[i] = Kruskal(i);//��������city,�ҵ�ÿ��city��cost
	}
	output();//�������
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
			break;//�����ͨ��break��
		city1 = city2 = 0;
		min = findmin(city);//�ҵ���Сcost��·��
		if (min == 0x7FFFFFFF) {
			return min;
		}//�޷��޸������
		V = find(city1);
		W = find(city2);//�ҵ�������ĸ��ڵ㣨�ж�����city�Ƿ�����ͨ
		if (V != W) {
			edge++;
			if (min>0) {
				costs = costs + min;//�����Ҫ�޸�������costs
			}
			DisjSet[W] = V;//��ͨ
		}
	}
	return costs;
}
int findmin(int conquer)
{
	int i = 0;


	int min = 0x7FFFFFFF;
	//���ȿ���state=1��highway��
	while (cost1[count1].c1 == conquer || cost1[count1].c2 == conquer) {
		count1++;
	}//�������ռ�������ǣ��޳���
	if (count1 <= p1) {
		city1 = cost1[count1].c1;
		city2 = cost1[count1].c2;
		min = cost1[count1].cost;
		count1++;//����ѡ��ĵ��޳�
		return -1 * min;
	}
	else {
		//��Ϊ��ͨ���ٿ���state=0��highway
		while (cost2[count2].c1 == conquer || cost2[count2].c2 == conquer) {
			count2++;
		}
		//������ռ�������ǣ��޳�
		if (count2 <= p2) {
			city1 = cost2[count2].c1;
			city2 = cost2[count2].c2;
			min = cost2[count2].cost;
			count2++;//����ѡ��ĵ��޳�
			return min;
		}
	}
	//������δ��ͨ������޷��޸�������һ����ֵ
	return min;


}


int find(int city)
{
	if (DisjSet[city] <= 0)
		return city;//�ҵ����ڵ㷵��
	else
		return DisjSet[city] = find(DisjSet[city]);//·��ѹ��
}


void output()
{
	int max = 0;
	int i = 0;
	int flag = 1;
	for (i = 1; i <= M; i++) {
		if (costp[i]>max)
			max = costp[i];
	}//�ҵ����cost
	if (max == 0)
		printf("0");//�������޸������0
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