#include <iostream>
#include <cstdio>
#include <time.h>
using namespace std;
#define value_type int
int n;
int num[1000000];
clock_t start, stop;
double duration;
double ticks, totaltime;

struct skip_node;
typedef struct skip_node *Node; //Node pointer
struct skip_node {
	int key;
	value_type value;
	Node forward[]; //pointer array
};

class skipList {
private:
	int MAX_LEVEL;  //store the max level
	int level;      //store the level of head
	int size;
	Node Head;      //head of the skip list
public:
	skipList(int M);//constructor
	~skipList();    //destructor
	Node CreateNode(const int level, const int key, const value_type value);
	bool Insert(const int key, const value_type value);
	bool Delete(const int key, const value_type value);
	bool Search(const int key, const value_type value);
	void Print();
};

skipList::skipList(int M)						//skipList construtor
{
	this->MAX_LEVEL = M;						//initialize the MAX_LEVEL
	this->Head = CreateNode(MAX_LEVEL, 0, 0);   //create the head node
	if (Head == NULL)
		exit(1);
	this->level = 0;							//the initial level = 0
	this->size = 0;								//the initial size = 0
	for (int i = 0; i < this->MAX_LEVEL; i++)
		Head->forward[i] = NULL;				//keep the pointer to NULL
}

skipList::~skipList()							//destructor
{
	Node p, q;									//new pointer
	for (p = Head; p != NULL; free(q))
	{											//free all the node
		q = p;
		p = p->forward[0];
	}
}

Node skipList::CreateNode(const int level, const int key, const value_type value)
{
	//create new node ask for the data and pointers
	Node newNode = (Node)malloc(sizeof(struct skip_node) + level * sizeof(Node));
	newNode->key = key;			//initialize the key
	newNode->value = value;		//initialize the value
	return newNode;
}

bool skipList::Insert(const int key, const value_type value)
{
	Node update[MAX_LEVEL];							    //a array to store the formar node
	Node p, q = NULL;
	p = Head;											//start from head

	for (int i = level - 1; i >= 0; i--)
	{													//start from the highest level
		while ((q = p->forward[i]) && (q->key<key))
			p = q;
		update[i] = p;									//store the record for later update
	}
	if (q&&q->key == key)
		return false;									//if the node already exist

	int k = rand() % MAX_LEVEL;							//use random function to determain the level
	if (k > level)
	{													//update the level
		for (int i = level; i<k; i++)
			update[i] = Head;
		level = k;
	}
	q = CreateNode(k, key, value);						//create a new node
	size++;												//increase the size
	for (int i = 0; i<k; i++) {
		q->forward[i] = update[i]->forward[i];			//use the update array
		update[i]->forward[i] = q;
	}
	return true;										//insert success
}

bool skipList::Delete(const int key, const value_type value)
{
	Node update[MAX_LEVEL];								//use the update array to update later
	Node p, q = NULL;
	p = Head;											//start from head
	for (int i = level - 1; i >= 0; i--)
	{													//start from the highest level
		while ((q = p->forward[i]) && (q->key < key))   //to find the key
			p = q;
		update[i] = p;
	}
	if (q&&q->key == key)
	{													//already find the node
		for (int i = 0; i<level; i++)
		{												//start from the bottom level
			if (update[i]->forward[i] == q)
				update[i]->forward[i] = q->forward[i];
		}
		free(q);										//delete the node
		for (int i = level - 1; i >= 0; i--)
		{
			if (Head->forward[i] == NULL)
				level--;
		}
		size--;											//decrease the size
		return true;
	}
	else
		return false;
}

bool skipList::Search(const int key, const value_type value)
{
	Node p, q = NULL;									//two new pointer
	p = Head;											//start from head
	for (int i = level - 1; i >= 0; i--)
	{													//start from highest level
		while ((q = p->forward[i]) && (q->key <= key))
		{												//while the pointer's key < key
			if (q->key == key)
				return true;							//if find the node
			p = q;										//update the pointer
		}
	}
	return false;										//can not find
}

void skipList::Print()
{
	for (int i = level - 1; i >= 0; i--)
	{
		Node temp = Head->forward[i];
		while (temp != NULL)
		{
			cout << "key " << temp->key << " value " << temp->value << " level " << i << endl;
			temp = temp->forward[i];
		}
	}
	Node temp = Head;
	for (int i = 0; i<size; i++)
	{
		cout << temp->key << " ";
		temp = temp->forward[0];
	}
	cout << endl;
}

int main()
{
	FILE *fp;
	fp = fopen("/Users/zhaoxuandong/Desktop/test.txt", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return -1;
	}
	int n;
	skipList sl(30);
	while (~fscanf(fp, "%d", &n))//for every test case
	{
		for (int i = 0; i<n; i++)//read in 
		{
			fscanf(fp, "%d", num + i);
		}
		start = clock();
		for (int i = 0; i<n; i++)
		{
			sl.Delete(num[i], num[i]);
		}
		stop = clock();
		ticks = ((double)(stop - start));
		totaltime = ticks / CLOCKS_PER_SEC;
		duration = totaltime;
		printf("ticks = %lf, total time(i) = %lf, duration(i) = %lf\n", ticks, totaltime, duration);
	}
	fclose(fp);
}
