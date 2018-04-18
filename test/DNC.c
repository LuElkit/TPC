#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <err.h>
#include <errno.h>


struct arg{
	double result;
	int* begin;
	int* end;
};
double lin_arry_sum(int * begin, int* end)
{
	double result =0;
	int len = end -begin;
	while(len >0)
	{
		result+=(double)*(begin+len-1);
		len-=1;
	}
	return result;
}

double dnd_sum(int *begin,int*end,int threashold)
{
	if(end -begin <threshold)
	{
		return lin_array_sum(begin,end);
	}
	int* mid = begin +(end-begin)/2;
	double a = dnd_sum(begin,mid);
	double b = dnd_sum(mid,end);
	return a+b;
}

void* worker(void* arg_)
{
	struct arg *arg =arg_;
	arg->result =dnd_sum(arg->begin,arg->end,arg->threshold);
	pthread_exit(NULL);
}

