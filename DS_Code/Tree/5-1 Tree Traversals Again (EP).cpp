#include <bits/stdc++.h>  
#define LL long long  
using namespace std;
char s[100], str[100];
struct node
{
	char c;
	node *l, *r;
};
node *build(int l, int r, int L, int R)
{
	node *head;
	if (l>r)
		return NULL;
	head = new node;
	head->c = s[l];
	int i;
	for (i = L; str[i] != s[l]; i++);
	head->l = build(l + 1, l + (i - L), L, i - 1);
	head->r = build(l + (i - L + 1), r, i + 1, R);
	return head;
}
void hou(node *head)
{
	if (head->l)
		hou(head->l);
	if (head->r)
		hou(head->r);
	printf("%c", head->c);
}
void ceng(node *head)
{
	queue<node*>Q;
	Q.push(head);
	node *tmp;
	while (!Q.empty())
	{
		tmp = Q.front(), Q.pop();
		printf("%c", tmp->c);
		if (tmp->l)
			Q.push(tmp->l);
		if (tmp->r)
			Q.push(tmp->r);

	}
	printf("\n");
}
int main()
{
	int t;
	node *head;
	cin >> t;
	while (t--)
	{
		scanf("%s%s", s, str);
		int len = strlen(s);
		head = build(0, len - 1, 0, len - 1);
		hou(head);
		printf("\n");
		ceng(head);
	}
	return 0;
}
