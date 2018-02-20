#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
void echo(size_t id) {
  int r;
  char buf[256];
  while ( (r = read(STDIN_FILENO, buf, 255)) ) {
    if (r == -1) {
      if (errno == EINTR) continue;
      err(2, "Issue reading from stdin in thread %zu", id);
    }
    buf[r] = 0;
    printf("<%02zu>: %s", id, buf);
  }
}

void* Thread(void* arg)
{
	size_t i = (size_t)arg;
	echo(i);
	pthread_exit(NULL);
}
int main(int argc, char** argv)
{
	if(argc<2)
	{
		printf("few arguments\n");
		return 0;
	}
	if(argc>2)
	{	
		printf("to much arguments");
		return 0;
	}
	size_t number = atoi(argv[1]);
	pthread_t thr[number];
	for(size_t i=0; i<number;i++)
	{
		int e=pthread_create(&thr[i],NULL,Thread,(void*)i);
		if(e!=0)
			errx(EXIT_FAILURE, "pthread_create()");
	}
	for(size_t j=0; j<number;j++)
	{
		int e= pthread_join(thr[j],NULL);
		if(e!=0)
			errx(EXIT_FAILURE,"pthread_join()");
	}
	pthread_exit(NULL);
}
