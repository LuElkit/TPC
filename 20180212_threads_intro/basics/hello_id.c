#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <pthread.h>
//#include <unistd.h>

struct th_arg{
	const char* msg;
	size_t id;
};

void* Print_id(void* arg)
{
	struct th_arg *donnee= arg;
	size_t ID= donnee->id;
	const char* msg= donnee->msg;
	printf("<%02zu>: %s \n",ID,msg);
	//sleep(1);
	pthread_exit(NULL);
}
int main(int argc, char** argv)
{
	if(argc <2)
	{
		printf("few arguments");
		return 0;
	}
	if(argc > 2)
	{
		printf("to much arguements");
		return 0;
	}
	size_t number= atoi(argv[1]);
	pthread_t thr[number];
	struct th_arg data[number];
	char *msg= "Hello from thread !";

	for(size_t i=0; i<number; i++)
	{
		data[i].msg= msg;
		data[i].id =i;
		int e= pthread_create(&thr[i],NULL,Print_id,&data[i]);
		if(e!=0)
			errx(EXIT_FAILURE,"pthread-create()");
	}
	for(size_t j=0; j<number; j++)
	{
		int e= pthread_join(thr[j],NULL);
		if(e!=0)
			errx(EXIT_FAILURE,"pthread_join()");
	}
	//pthread_exit(NULL);
	
}
