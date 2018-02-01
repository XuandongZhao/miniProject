Polynomial Add( Polynomial a, Polynomial b ){
	Polynomial ptr1, ptr2, ptr3, ptr4, head;
	ptr4 = (Polynomial)malloc(sizeof(Polynomial));
	ptr4->Next=NULL;
	head = NULL;
	ptr1 = a;
	ptr2 = b; 
	int num;
	//ptr3 = (Polynomial)malloc(sizeof(Polynomial));
	while(ptr1 != NULL || ptr2 != NULL){
		ptr3 = (Polynomial)malloc(sizeof(Polynomial));
		if(ptr1 == NULL){
			ptr3->Coefficient = ptr2->Coefficient;
			ptr3->Exponent = ptr2->Exponent;
			ptr2 = ptr2->Next;
		}
		else if(ptr2 == NULL){
				ptr3->Coefficient = ptr1->Coefficient;
				ptr3->Exponent = ptr1->Exponent;
				ptr1 = ptr1->Next;
			}
			else if(ptr1->Exponent == ptr2->Exponent){
					num = (ptr1->Coefficient) + (ptr2->Coefficient);
					if(num)
					{	
						ptr3->Coefficient = num;
						ptr3->Exponent = ptr2->Exponent;
					}
					ptr1 = ptr1->Next;
					ptr2 = ptr2->Next;
				}
				else if(ptr1->Exponent > ptr2->Exponent){
						ptr3->Coefficient = ptr1->Coefficient;
						ptr3->Exponent = ptr1->Exponent;
						ptr1 = ptr1->Next;
					}
					else{
						ptr3->Coefficient = ptr2->Coefficient;
						ptr3->Exponent = ptr2->Exponent;
						ptr2 = ptr2->Next;
					}
		ptr3->Next = NULL;
		if(!head)
			head = ptr3;
		else
			ptr4->Next = ptr3;
		ptr4 = ptr3;
	}
	return head;
}
