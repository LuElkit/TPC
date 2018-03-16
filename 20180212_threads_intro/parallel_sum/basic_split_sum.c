#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

struct forme{
		int* begin;
		int* end;
		double result;
};

double lin_array_sum(int* begin, int* end)
{
	double result=0;
	int len = end-begin;
	while(len >0)
	{
		result += (double)*(begin+len -1);
		len-=1;
	}
	return result;
}
void* My_Thread_run(void* arg)
{
	struct forme* data = arg;
	data->result = lin_array_sum(data->begin,data->end);
	pthread_exit(NULL);
}

double basic_split_sum(int *begin,int* end, int nbthr)
{
	pthread_t workers[nbthr];
	struct forme data[nbthr];//calloc(nbthr,sizeof(struct forme));
	int len = (end - begin)/ nbthr;
	int* cur = begin;

	for(int i=0 ; i< nbthr; i++)
	{
		data[i].begin =cur;
		if(end < cur+len)
			data[i].end = end;	
		else
		{
			data[i].end = cur+len;
		}
		int e = pthread_create(&workers[i],NULL,My_Thread_run,(void *)&data[i]);
		if(e!=0)
			errx(EXIT_FAILURE,"phread_create()");
		cur =cur + len;
	}
	double result =0;
	for(int j =0; j< nbthr; j++)
	{
		int e = pthread_join(workers[j],NULL);
		if(e!= 0)
			errx(EXIT_FAILURE,"pthread_join()");
		result= result +data[j].result;
	}
	return result;
}
int main(int argc, char**argv)
{
	if(argc <3)
		return 0;
	int size= atoi(argv[1]);
	int nbthr = atoi(argv[2]);
	int* begin = calloc(size, sizeof(int));
	int* end = begin + size;
	for(int i = 0; i < size ; i++)
			*(begin + i) = 10000 + i;
	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = localtime(&rawtime);
	double res = basic_split_sum(begin, end,nbthr);
	printf("basic_split_sum : %.2f, time: %d\n",res,info->tm_sec);
	time_t timer;
	struct tm *timerS;
	time(&timer);
	timerS = localtime(&rawtime);
	double resT = lin_array_sum(begin,end);
	printf("lin_array_sum : %.2f, time : %d\n", resT,timerS->tm_sec);
	free(begin);
}
/*int *data = malloc(10)

begin == data
end == data + 10

struct array[nbthread];
if nb thread == 2
array[0] array[1]*/


