#include<stdio.h>
#include<stdlib.h>
int main()
{
	struct student 
	{
		long int number;
		char name[20];
		char sex;
		char address[20];
		
	} a={315010491,"li lin",'M',"123Beijing Road"};
	printf("NO:%ld\nname:%s\nsex:%c\naddress:%s\n",a.number,a.name,a.sex,a.address);
	return 0;
}
