#include<stdio.h>  
#include<stdlib.h>  
#define MaxSize 10000  

enum { black, red };

typedef struct TreeNode {
		int key;
			int color;
				struct TreeNode *right;
					struct TreeNode *left;
						struct TreeNode *parent;
}*RedBlackTree;

RedBlackTree T_NIL;

void LeftRotate(RedBlackTree &T, RedBlackTree x)
{
		RedBlackTree y;
			y = x->right;
				x->right = y->left;
					if (y->left != T_NIL) {
								y->left->parent = x;
									}
						y->parent = x->parent;
							if (x->parent == T_NIL) {
										T = y;
											}
								else if (x == x->parent->left) {
											x->parent->left = y;
												}
									else x->parent->right = y;
										y->left = x;
											x->parent = y;
}

void RightRotate(RedBlackTree &T, RedBlackTree x)
{
		RedBlackTree y;
			y = x->left;
				x->left = y->right;
					if (y->right != T_NIL) {
								y->right->parent = x;
									}
						y->parent = x->parent;
							if (x->parent == T_NIL) {
										T = y;
											}
								else if (x == x->parent->right) {
											x->parent->right = y;
												}
									else x->parent->left = y;
										y->right = x;
											x->parent = y;
}

//插入调整

void InsertFixup(RedBlackTree &T, RedBlackTree z)
{
		RedBlackTree y;
			while (z->parent->color == red) { //新插入结点的父节点为红色时，进行调整
						//第一种情况，父节点是左孩子
						if (z->parent == z->parent->parent->left) {
										y = z->parent->parent->right;
													// Case 1
													if (y->color == red) { 
																		z->parent->color = black; // 父节点颜色由红变黑
																						y->color = black; // 父节点的兄弟颜色也由红变黑
																										z->parent->parent->color = red; //祖父结点由黑变红
																														z = z->parent->parent; // 更新当前节点为祖父结点，以继续向上调整
																																	}
																// Case 2 ( 先转化为Case 3 ）
																else {   
																					if (z == z->parent->right) {
																											z = z->parent; //左旋变成Case 3
																																LeftRotate(T, z);
																																				}
																									// Case 3
																									z->parent->color = black; //父节点由红变黑
																													z->parent->parent->color = red; //祖父节点由黑变红
																																	RightRotate(T, z->parent->parent);//右旋
																																				}
																		}
								//第二种情况，父节点是右孩子（与前面对称）
								else if (z->parent == z->parent->parent->right) {
												y = z->parent->parent->left;
															if (y->color == red) { // Case 1
																				z->parent->color = black;
																								y->color = black;
																												z->parent->parent->color = red;
																																z = z->parent->parent;
																																			}
																		else {   // Case 2 ( 先转化为Case 3 ）
																							if (z == z->parent->left) {
																													z = z->parent;
																																		RightRotate(T, z);
																																						}
																											// Case 3
																											z->parent->color = black;
																															z->parent->parent->color = red;
																																			LeftRotate(T, z->parent->parent);
																																						}
																				}
									}
				T->color = black;
}

//插入（非递归）

void Insert(RedBlackTree &T, int num)
{
		RedBlackTree x, y, z;
			if (!T) { //如果树为空
						T_NIL = (RedBlackTree)malloc(sizeof(struct TreeNode)); //外部叶结点申请内存
								T = (RedBlackTree)malloc(sizeof(struct TreeNode)); //根结点申请内存
										T->parent = T_NIL; //根结点父节点为NIL
												T->color = black; //根结点颜色为黑色
														T->left = T_NIL; //左子树为空叶结点
																T->right = T_NIL; //右子树为空叶结点
																		T->key = num; //存储数据
																				T_NIL->color = black;  //设置空叶结点颜色为黑色
																					}
				else { //如果树不为空
							z = (RedBlackTree)malloc(sizeof(struct TreeNode)); //申请新建结点空间
									y = T_NIL; // 初始化y，y将记录新建结点的父节点
											x = T; //初始化x为T，用于跟踪插入位置
													//以下循环找到插入位置
													while (x != T_NIL) { 
																	y = x; //记录父节点位置
																				if (num<x->key)x = x->left;  //小于key，向左搜索
																							else if (num>x->key)x = x->right; //大于key，向右搜索
																										else return; //等于key，该结点已存在，无需插入，返回
																												}
															//找到插入位置，y是父节点，根据大小判断新建结点是左子树还是右子树，并更新
															if (num<y->key)y->left = z;
																	else y->right = z;
																			z->left = T_NIL;//初始化新建结点的左孩子右孩子为空
																					z->right = T_NIL;
																							z->color = red;//初始化新建结点的颜色为红色
																									z->parent = y;//更新父节点为y
																											z->key = num;//存储数据
																													InsertFixup(T, z);//调用插入调整函数
																														}
					return;
}

//用v结点及其子树取代u结点
void Transplant(RedBlackTree &T, RedBlackTree u, RedBlackTree v)
{
		if (u->parent == T_NIL) {//u是根节点
					T = v;
						}
			else if (u == u->parent->left) {//u是左子树
						u->parent->left = v;
							}
				else u->parent->right = v;//u是右子树
					v->parent = u->parent;//无条件更新父母
						return;
}

//寻找后继
RedBlackTree TreeMinimum(RedBlackTree x) {
		while (x->left != T_NIL) {
					x = x->left;
						}
			return x;
}

//删除调整
void DeleteFixup(RedBlackTree &T, RedBlackTree x)
{
		RedBlackTree w;
			while (x != T&&x->color == black) {
						if (x == x->parent->left) { 
										w = x->parent->right;
													if (w->color == red) { // case 1：x's sibling w is red
																		w->color == black; //兄弟的颜色变为黑色
																						x->parent->color == red; //父母变为红色
																										LeftRotate(T, x->parent);//左旋
																														w = x->parent->right;
																																	}
																// case 2: x's sibling w is black and both of it's child is black
																if (w->left->color == black&&w->right->color == black) {
																					w->color = red;
																									x = x->parent;
																												}
																			// case 3: x's sibling is black,w'left child is red,and right child is black
																			else {
																								if (w->right->color == black) {
																														w->left->color = black;
																																			w->color = red;
RightRotate(T, w);
																																													w = x->parent->right;
																																																	}
																												// case 4:x's sibling w is black and w's right child is red
																												w->color = x->parent->color;
																																x->parent->color = black;
																																				w->right->color = black;
																																								LeftRotate(T, x->parent);
																																												x = T;
																																															}
																					}
								else {
												w = x->parent->left;
															if (w->color == red) {
																				w->color == black;
																								x->parent->color == red;
																												RightRotate(T, x->parent);
																																w = x->parent->left;
																																			}
																		if (w->right->color == black&&w->left->color == black) {
																							w->color = red;
																											x = x->parent;
																														}
																					else {
																										if (w->left->color == black) {
																																w->right->color = black;
																																					w->color = red;
																																										LeftRotate(T, w);
																																															w = x->parent->left;
																																																			}
																														w->color = x->parent->color;
																																		x->parent->color = black;
																																						w->left->color = black;
																																										RightRotate(T, x->parent);
																																														x = T;
																																																	}
																							}
									}
				x->color = black;
				        return;
}

RedBlackTree Search(RedBlackTree T, int x)
{
		while (x != T->key&&T != T_NIL) {
					if (x>T->key)T = T->right;
							else T = T->left;
								}
			return T;
}

//删除

void Delete(RedBlackTree &T, int num)
{
		RedBlackTree z = Search(T, num); //先找到要删除的节点
			RedBlackTree x, y = z;
				int y_OriginalColor = y->color; //记录要删除节点的颜色
					if (z->left == T_NIL) { //被删结点只有右子树
								x = z->right;
										Transplant(T, z, z->right);//用右子树代替被删结点
											}
						else if (z->right == T_NIL) {//被删结点只有左子树
									x = z->left;
											Transplant(T, z, z->left);//用左子树代替被删结点
												}
							else {//被删结点既有左子树又有右子树
										y = TreeMinimum(z->right);//找到后继
												y_OriginalColor = y->color;
														x = y->right;//x为后继右孩子
																if (y->parent == z)//如果后继恰是被删结点的孩子
																				x->parent = y;
																		else {//如果后继不是被删结点的孩子
																						Transplant(T, y, y->right);//用后继的右孩子代替后继
																									y->right = z->right;//用后继取代被删结点
																												y->right->parent = y;
																														}
																				Transplant(T, z, y);//用后继取代被删结点
																						y->left = z->left;
																								y->left->parent = y;
																										y->color = z->color;
																											}
								if (y_OriginalColor == black)//删除的是黑色节点
											DeleteFixup(T, x);//调整
									return;
}

struct QueueNode {
		RedBlackTree data[MaxSize];
			int rear;
				int front;
}queue;

struct QueueNode *p = &queue;

void Enqueue(RedBlackTree T) {
		p->rear = (p->rear + 1) % MaxSize;
			p->data[p->rear] = T;
}

RedBlackTree Dequeue() {
		p->front = (p->front + 1) % MaxSize;
			return p->data[p->front];
}

bool IsEmpty() {
		if (p->front == p->rear)return true;
			else return false;
}

void InOrderTraversal(RedBlackTree T)
{
		if (T != T_NIL) {
					printf("%d ", T->key);
							if (T->parent!=T_NIL)printf("parent=%d\n", T->parent->key);
									else printf("parent=null\n");
											switch (T->color) {
														case(black) : printf("color=black\n"); break;
																	  		case(red) : printf("color=red\n"); break;
																								}
													InOrderTraversal(T->left);
															InOrderTraversal(T->right);
																}
			return;
}

void LevelOrderTraversal(RedBlackTree T)
{
		printf("%d ", T->key);
			Enqueue(T);
				while (!IsEmpty()) {
							T = Dequeue();
									if (T->left != T_NIL) {
													printf("%d ", T->left->key);
																Enqueue(T->left);
																		}
											if (T->right != T_NIL) {
															printf("%d ", T->right->key);
																		Enqueue(T->right);
																				}
												}
					return;
}


int main()
{
		p->front = p->rear = 0;
			RedBlackTree T = NULL;
				int i;
					int n,x;
						scanf("%d", &n);
							for (i = 0; i < n; i++) {
										scanf("%d", &x);
												Insert(T, x);
													}
								InOrderTraversal(T);
									printf("\n");

										system("pause");
											return 0;
}

