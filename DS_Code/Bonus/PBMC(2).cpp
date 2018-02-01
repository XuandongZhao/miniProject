#include <stdio.h>

#define MAX_VERTICES 501
#define INF 1000000000
#define MAXBIKE 50000

int CMAX, N, M, IP;
struct Table {
	int dist;
	int known;
	int pre;
	int bike;
	int need;
	int back;
} T[MAX_VERTICES];
int Cost[MAX_VERTICES][MAX_VERTICES];

int choose()
{
	int i, minD = INF, minI;
	for( i=0; i<=N; i++ )
		if ( (!T[i].known) && (T[i].dist < minD) ) {
			minD= T[i].dist;
			minI= i;
		}
	return minI;
}

void ShortestPath ( int IP, int *Nsend, int *Nreturn )
{   int  i, u, w, ThisNeed;

    for  ( i = 0; i <= N; i++ )  {
        T[i].known = 0;
        T[i].dist = Cost [ IP ] [ i ] ;
    }
    T[IP].known = 1;
    T[IP].dist = 0 ;
	if (T[0].dist < INF) { /* 0 is connected to IP */
		T[0].pre = IP;
		if (T[IP].need>0) T[0].need = T[IP].need;
		else { T[0].back = 0; T[0].need = 0; }
	}
    for  ( i = 0; i < N-1; i++ )  {
        u = choose();
		if ( u==0 ) break;
        T[u].known = 1;
		if (T[u].need == MAXBIKE) { /* directly connected to IP */
			T[u].pre = IP;
			T[u].need = CMAX - T[u].bike;
			if (T[IP].need > 0) T[u].need += T[IP].need;
			if (T[u].need<0) T[u].back = -T[u].need;
			else T[u].back = 0;
		}
        for  ( w = 0; w < N; w++ )
            if ( !T[w].known )
				if ( T[u].dist + Cost[ u ][ w ] < T[w].dist ) { /* Update */
                    T[w].dist = T[u].dist + Cost[ u ][ w ];
					if ( (CMAX-T[w].bike > 0) && (T[u].need < 0) ) {
					/* if u no need, but w need */
						T[w].need = CMAX-T[w].bike; /* only balance w */
						T[w].back = T[u].back; /* take u back */
					}
					else { /* if u need or w self no need */
						T[w].need = CMAX + T[u].need - T[w].bike;
						if (T[w].need < 0)  T[w].back = -T[w].need;
						else T[w].back = T[u].back; /* if w need, balance w and take u back */
					}
					T[w].pre = u;
				}
				else if (T[u].dist + Cost[ u ][ w ] == T[w].dist) {
					if ( (CMAX-T[w].bike > 0) && (T[u].need < 0) )
						ThisNeed = CMAX-T[w].bike; /* if u no need, but w need */
					else
						ThisNeed = CMAX + T[u].need - T[w].bike;
					if ( ( (T[w].need > 0) && (ThisNeed < T[w].need) ) || 
						( (T[w].need <= 0) && (ThisNeed <= 0) && (ThisNeed > T[w].need) ) ) {
					/* case1: w need and now need less; case2: both no need and now back less */
						T[w].need = ThisNeed;
						T[w].pre = u; /* Update */
						if (T[w].need < 0)  T[w].back = -T[w].need;
						else T[w].back = T[u].back;/* if w need, balance w and take u back */
					}
				}
    }
	*Nsend = T[0].bike - CMAX + T[0].need;
	if (*Nsend < 0) {
		*Nreturn = -*Nsend;
		*Nsend = 0;
	}
	else
		*Nreturn = T[T[0].pre].back;
	if (T[IP].need <0) *Nreturn -= T[IP].need;
}

int main()
{
	int i, j, u, v;
	int Nsend, Nreturn;

	scanf("%d %d %d %d", &CMAX, &N, &IP, &M);
	CMAX /= 2;
	for (i=0; i<=N; i++)
		for (j=0; j<=N; j++)
			Cost[i][j] = INF;
	T[0].bike = CMAX;
	for (i=1; i<=N; i++) {
		scanf("%d", &T[i].bike);
		T[i].known = 0;
		T[i].need = MAXBIKE;
	}
	T[IP].need = CMAX - T[IP].bike;
//	if (T[IP].need < 0)  T[IP].back = -T[IP].need;
//	else T[IP].back = 0;
	T[IP].back = 0;
	for (i=0; i<M; i++) {
		scanf("%d %d", &u, &v);
		scanf("%d", &Cost[u][v]);
		Cost[v][u] = Cost[u][v];
	}
	ShortestPath( IP, &Nsend, &Nreturn );
	printf("%d 0", Nsend);
	v = 0;
	while (T[v].pre != IP) {
		printf("->%d", T[v].pre);
		v = T[v].pre;
	}
	printf("->%d %d\n", IP, Nreturn);

	return 0;
}
