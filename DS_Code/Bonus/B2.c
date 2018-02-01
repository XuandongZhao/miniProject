#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
int x;
int y;
int c;
};

int f[505], num[505];
vector<node> e;

bool cmp(const node &x, const node &y) {
        return x.c < y.c;
}

int getf(int x) {
        return (f[x] == x)?x:(f[x] = getf(f[x]));
}

bool make(int x,int y) {
        if ((x = getf(x)) == (y = getf(y))) {
                return false;
        }
        if (num[x] < num[y]) {
                f[x] = y;
                num[y] += num[x];
        }
        else {
                f[y] = x;
                num[x] += num[y];
        }
        return true;
}

int main() {
int n, m;
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; ++i) {
                int x, y, c, p;
                scanf("%d%d%d%d",&x, &y, &c, &p);
                node temp;
                temp.x = x - 1;
                temp.y = y - 1;
                temp.c = p?0:c;
                e.push_back(temp);
        }
        sort(e.begin(), e.end(), cmp);
        vector<int> answer;
        int now = 1;
        bool mark = false;
        for (int i = 0; i < n; ++i) {
                int need = n - 2;
                int cost = 0;
                for (int j = 0; j < n; ++j) {
                        f[j] = j;
                        num[j] = 1;
                }
                for (int j = 0; (need > 0) && (j < m); ++j) {
                        if ((e[j].x != i) && (e[j].y != i) && make(e[j].x, e[j].y)) {
                                --need;
                                cost += e[j].c;
                        }
                }
                if (need > 0) {
                        if (!mark) {
                                mark = true;
                                answer.clear();
                        }
                        answer.push_back(i);
                }
                else if (mark) {
                }
                else if (cost > now) {
                        now = cost;
                        answer.resize(1);
                        answer[0] = i;
                }
                else if (cost == now) {
                        answer.push_back(i);
                }
        }
        if (answer.empty()) {
                puts("0");
        }
        else {
                for (int i = 0; i < answer.size(); ++i) {
                        if (i) {
                                putchar(' ');
                        }
                        printf("%d",answer【i】 + 1);
                }
                puts("");
        }
        return 0;
}
