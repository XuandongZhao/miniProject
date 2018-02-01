#include<iostream>  
#include<vector>  
using namespace std;
#define inf 999999  
int cmax, n, sp, m, send, back;
int bike[505] = { 0 };
int route[505][505] = { { 0 } };
int visit[505] = { 0 };
int minsend = inf, minback = inf, mindis = inf;
vector<int> path, temppath;
void dfs(int v, int tempsend, int tempback, int tempdis)
{
	temppath.push_back(v);
	visit[v] = 1;
	if (v == sp)
	{
		if (mindis > tempdis)
		{
			minsend = tempsend;
			minback = tempback;
			mindis = tempdis;
			path = temppath;
		}
		else if (mindis == tempdis)
		{
			if (minsend > tempsend)
			{
				minsend = tempsend;
				minback = tempback;
				path = temppath;
			}
			else if (minsend == tempsend && minback > tempback)
			{
				minback = tempback;
				path = temppath;
			}
		}
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		if (visit[i] == 0 && route[v][i] != inf)
		{
			int temp = bike[i] - cmax;
			int tempb = tempback, temps = tempsend;
			if (temp >= 0)
				tempb += temp;
			else
			{
				if (tempback + temp < 0)
				{
					temps -= (tempback + temp);
					tempb = 0;
				}
				else
					tempb += temp;
			}
			dfs(i, temps, tempb, tempdis + route[v][i]);
			temppath.pop_back();
			visit[i] = 0;
		}
	}
}
int main()
{
	scanf("%d%d%d%d", &cmax, &n, &sp, &m);
	cmax /= 2;
	fill(route[0], route[0] + 505 * 505, inf);
	for (int i = 0; i < n; i++)
		scanf("%d", &bike[i + 1]);
	for (int i = 0; i < m; i++)
	{
		int ti, tj, v;
		scanf("%d%d%d", &ti, &tj, &v);
		route[ti][tj] = route[tj][ti] = v;
	}
	dfs(0, 0, 0, 0);
	printf("%d ", minsend);
	for (int i = 0; i < path.size(); i++)
	{
		if (i != 0)
			printf("->");
		printf("%d", path[i]);
	}
	printf(" %d", minback);
	return 0;
}
