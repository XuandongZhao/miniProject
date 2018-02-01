#include <stdio.h>
#include <stdlib.h>
#define MaxCapacityNum 100
#define MaxStationNum 500
#define INFINITY 1000000

typedef int WeightType;
typedef struct Station *PtrtoStation;
struct Station
{
	int C;   //the maximum capacity of each station
	int N;   //the total number of staions
	int Sp;  //the index of the problem station
	int M;   //the number of roads
	int *Ci; //Ci is the current number of bikes at Si respectively
	WeightType *T[MaxStationNum + 1]; //Tij is the time taken to move between station Si and Sj
									  /*If we store half of the matrix Tij, we can save the space
									  while we may need a judge when we use Tij, which increases time complexity*/
};

/*initialize the optimum solution/value*/
/*Param:    int mindis/missend/minback   minimum value of the best path*/
/*Param:    int dis/send/back            important value of the current path*/
/*Param:    BestPath[MaxStationNum+1]    record the best path in the problem*/
/*Param:    Path[MaxStationNum+1]        record the current path in the problem*/
int mindis = INFINITY, minsend = INFINITY, minback = INFINITY;
int dis = 0, send = 0, extra = 0;
int BestPath[MaxStationNum + 1] = { 0 }, Path[MaxStationNum + 1] = { 0 };
int end = 0;                     //mark the next index of the current path
int visit[MaxStationNum + 1] = { 0 };//mark whether the node is visited or not

									 /*claim two funtions used in the problem*/
PtrtoStation ReadS();
void DFS(PtrtoStation S, int node);

int main(void)
{
	PtrtoStation S = ReadS();//build a graph to describe network of stations
	int i = 1;               //used for iteration
	DFS(S, 0);               //use DFS to solve the problem and the starting point is 0(PBMC)
	printf("%d 0", minsend);  //output the final solution
	while (BestPath[i] != 0)
	{
		printf("->%d", BestPath[i]);
		i++;
	}
	printf(" %d", minback);
}

/*Function: ReadS*/
/*Brief:    build a graph to describe the network of stations*/
/*Param:    void*/
/*Retval:   PtrtoStation*/
PtrtoStation ReadS()
{
	PtrtoStation S;
	int i, j, line, row;
	int LineNum, RowNum;  //the number of lines and rows
	S = (PtrtoStation)malloc(sizeof(struct Station)); //apply dynamic memory for the structure
													  //Then input the value to decide the problem and there are some restrictions mentioned in it
	scanf("%d", &(S->C));
	while (S->C <= 0 || S->C % 2 != 0 || S->C > MaxCapacityNum)
	{
		printf("Wrong input! Please input an even number between 1 and 100.\n");
		scanf("%d", &(S->C));
	}

	scanf("%d", &(S->N));
	while (S->N <= 0 || S->N > MaxStationNum)
	{
		printf("Wrong input! Please input an integer between 1 and 500.\n");
		scanf("%d", &(S->N));
	}
	LineNum = RowNum = S->N + 1;

	scanf("%d", &(S->Sp));
	while (S->Sp <= 0 || S->Sp > S->N)
	{
		printf("Wrong input! Please input an integer between 1 and number of stations.\n");
		scanf("%d", &(S->Sp));
	}

	scanf("%d", &(S->M));
	while (S->M <= 0 || S->M > (S->N * (S->N + 1)) / 2)//the maximum number of edges is (S->N * (S->N + 1))/2
	{
		printf("Wrong input! Please input an integer between 1 and N(N+1)/2.\n");
		scanf("%d", &(S->M));
	}

	S->Ci = (int*)malloc(RowNum * sizeof(int));
	for (i = 0; i < LineNum; i++)
		S->T[i] = (int*)malloc(RowNum * sizeof(int));
	/*Dynamic application of two-dimensional array to save space*/

	S->Ci[0] = 0;
	for (i = 0; i <= S->N; i++)
	{
		for (j = 0; j <= S->N; j++)
			S->T[i][j] = 0;
	}
	for (i = 1; i <= S->N; i++)
	{
		scanf("%d", S->Ci + i);
		/*initialize vertex of the graph*/
	}
	for (i = 1; i <= S->M; i++)
	{
		scanf("%d", &line);
		scanf("%d", &row);
		scanf("%d", &S->T[line][row]);
		S->T[row][line] = S->T[line][row];
		/*input the value of edges*/
		/*Note: Because it's an undirected graph, so the matrix is symmetrical*/
	}
	return S;
}

/*Function: DFS*/
/*Brief:    use DFS to find the best path*/
/*Param:    PtrtoStation S   the target problem/graph*/
/*Param:    int node         the starting point*/
/*Retval:   void*/
void DFS(PtrtoStation S, int node)
{
	int i = 1, j = 1;        //used for iteration
	int LastSend, LastExtra; //used for backtracking 
	int success = 0;
	if (dis > mindis)        //reduce branches to reduce complexity
		return;
	Path[end] = node; //mark the visited node in the current path
	if (node == S->Sp) //one return condition is that we reach the end successfully
	{
		success = 0;
		if (dis < mindis) //the first successful condition(the shortest path)
			success = 1;
		else if (dis == mindis)
		{
			if (send < minsend)
				//the second successful condition(the least number of bikes sent from PBMC)
				success = 1;
			else if (send == minsend)
			{
				if (extra < minback)
					//the third successful condition(which is not clearly mentioned in the problem)
					success = 1;
			}
		}
		if (success == 1)
		{
			while (BestPath[j] != 0)   //First, clear the best path before
			{
				BestPath[j] = 0;
				j++;
			}
			for (i = 1; i <= end; i++)//Then, record the new best path
				BestPath[i] = Path[i];
			/*update the key value of the problem*/
			mindis = dis;
			minsend = send;
			minback = extra;
		}
		return;
	}
	visit[node] = 1; //DFS method to traverse the graph
	for (i = 1; i <= S->N; i++) //the ending point of DFS is the time when we traverse completely
	{
		if (visit[i] != 1 && S->T[node][i] > 0)//find the way connected with node
		{
			dis += S->T[node][i];
			//record the value of send and extra so that it's convenient when backtracking
			LastSend = send;
			LastExtra = extra;
			if (S->Ci[i] + extra < (S->C) / 2)
				//if the bikes in the stations and extra now are less than the perfect condition, then we need send bikes
			{
				send += (S->C) / 2 - (S->Ci[i] + extra);
				extra = 0;
			}
			else
				//otherwise we just use extra or not to solve the problem
			{
				extra = S->Ci[i] + extra - (S->C) / 2;
			}
			end++;
			Path[end] = node;
			DFS(S, i);      //DFS further
							/*finish one branch and backtrack*/
			Path[end--] = 0;
			visit[i] = 0;
			dis -= S->T[node][i];
			send = LastSend;
			extra = LastExtra;
		}
	}
}