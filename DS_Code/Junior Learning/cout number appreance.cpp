#include <stdio.h>

int Count_Digit ( const int N, const int D );

int main()
{
    int N, D;
				
    scanf("%d %d", &N, &D);
    printf("%d\n", Count_Digit(N, D));
    return 0;
}

int Count_Digit(const int N, const int D)
{
	int n, i, u;
	i = 0;
	if (N<0) n = -N;
	else n = N;
	while (n)
	{
		u = n % 10;
		n = n / 10;
		if (u == D) i++;
	}
	return i;
}