#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <time.h>
#include <math.h>
double  double_difftime(struct timespec *t0,struct timespec *t1)
{
	double  seconds0 =(double)t0->tv_sec;
	double  seconds1= (double)t1->tv_sec;
	double  res = seconds1-seconds0;
	return res;
}
#define TIMING_CODE(BLK__, RES__)	    \
    do {				    \
      struct timespec t0, t1;		    \
      clock_gettime(CLOCK_MONOTONIC, &t0);  \
      BLK__;				    \
      clock_gettime(CLOCK_MONOTONIC, &t1);  \
      RES__ = double_difftime(&t0, &t1);    \
    } while (0)	

int main()
{
	double runtime;
	for(int i=0; i < 10; i++)
	{
		TIMING_CODE(sleep(i),runtime);
		printf("%d : %lf\n",i,runtime);
	}
}
