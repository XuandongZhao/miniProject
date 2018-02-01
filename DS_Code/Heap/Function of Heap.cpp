/*Max Heap*/
typedef struct HeapStruct *Maxheap;
struct HeapStruct
{
	ElementType *Elements;
	int Size;
	int Capacity;
};
Maxheap Create(int MaxSize)
{
	Maxheap H = malloc(sizeof(struct HeapStruct));
	H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = MaxData;

	return H;
}
void Insert(Maxheap H, ElementType item)
{
	int i;
	if (IsFull(H))
	{
		printf("最大堆已满");
		return;
	}
	i = ++H->Size;
	for (; H->Elements[i / 2] < item; i /= 2)//需要设置哨兵
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = item;
}
