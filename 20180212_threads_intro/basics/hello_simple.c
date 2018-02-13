#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <pthread.h>


void* Print(void* arg)
{
  (void)arg;
	printf("Hello from thread !\n");
	pthread_exit(NULL);
}



int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("few arguments\n");
		return 0;
	}
	if(argc>2)
	{
		printf("to much arguments\n");
		return 0;
	}
  int number= atoi(argv[1]);
	pthread_t thr[number];
	for(int i=0; i<number;i++)
	{
		int e= pthread_create(&thr[i],NULL,Print,NULL);
		if(e!=0)
			errx(EXIT_FAILURE,"pthread_create()");
	}
	for(int j=0; j<number;j++)
	{
		int e=pthread_join(thr[j],NULL);
		if(e!=0)
			errx(EXIT_FAILURE,"pthread_join()");
	}
	pthread_exit(NULL);
}
