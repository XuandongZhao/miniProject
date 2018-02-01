#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

ElementType EvalPostfix( char *expr )
{
	double a[100];
	int i;
	int flag;
	flag = 0;
	for(i=0;expr[i];i++)
	{
		if(i==0)
		{
			if((expr[i]!=' ')&&!(expr[i]>='0'&&expr[i]<=9))
			flag = 1;
		}
		else 
		{
			if(expr[])
		}
	}
}