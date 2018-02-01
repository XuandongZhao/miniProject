#include <time.h>
#include <stdio.h>
#include"P2.cpp" 
#define REPEAT 1000 /*the repeat times of function Pow*/
clock_t start, stop;

int main(void)
{
    double ticks, totaltime, duration;
	start = clock(); /*the ticks at the begining of the function call*/
	fun()
		stop = clock(); /*the ticks at the end of the function call*/
		ticks = ((double)(stop - start));
		totaltime =  ticks / CLOCKS_PER_SEC;
		duration = totaltime / (double) REPEAT;
		printf ("ticks(%d) = %lf, total time(i) = %lf, duration(i) = %lf\n", i, ticks, totaltime, duration);
	
	
	return 1;
}
