#include<iostream>
#include<string>
//#include<stdlib.h>

using namespace std;

struct problem {
	string name;
	int t;
	int d;
};



int h, n, t0,l;
int totaltime = 0x7fffffff;
int ans[10];
int tmpans[10];
int pick[10];
problem Q[10];
bool md;

void Backtracking(int i,int tt,int tf);
void update(int i,int tt);

int main() {
	int last_total_time = 0x7fffffff;
	cin >> h;
	while (h >= 0) {
		l = 0;
		cin >> n >> t0;
		for (int i = 0; i < n; i++)
			cin >> Q[i].name >> Q[i].t >> Q[i].d;


		for(int k = 0;k<n;k++){
			pick[k] = 1;
			tmpans[0] = k;
			Backtracking(0,0,t0);
			pick[k] = 0;
		}
		if(!md)  totaltime = 0;
		else md =0;
		cout << "Total Time = " << totaltime << endl;
		last_total_time = totaltime;
		for (int j = 0; j < l; j++)
			cout << Q[ans[j]].name << endl;

		cin >> h;
	}

	return 0;
}


void update(int i,int tt){
	if(i<l)	return;
	if(i==l&&tt>=totaltime)	return;
	md = 1;
	l = i;
	totaltime = tt;
	for(int k=0;k<l;k++)
		ans[k] = tmpans[k];

}

void Backtracking(int k,int tt,int tf) {

	int firstsub = tf + Q[tmpans[k]].t;
	int times = (firstsub%60==0)?(firstsub/60-1):(firstsub/60);
	int timeflash = tf + Q[tmpans[k]].d*times +Q[tmpans[k]].t;
	int t = tt + timeflash + 20*times;

	if(timeflash>h*60)  return;
//	if(k==n-1)		return;
//		update(k,t);
		k++;
		for(int i = 0; i<n;i++){
			if(pick[i]==0){
				pick[i] = 1;
				tmpans[k] = i;
				Backtracking(k,t,timeflash);
				pick[i] = 0;
			}
		}
		update(k,t);
}



