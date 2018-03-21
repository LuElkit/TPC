#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <pthread.h>
#include "../queue/shared_queue.h"
void echo(int fdin, int fdout)
{
  char buf[1];
  ssize_t ok;
  while((ok=read(fdin,buf,1)))
  {
		if(ok == -1)
			err(3,"READ FAIL");
    if(errno==EINTR||errno==EAGAIN||errno==EWOULDBLOCK)	
      continue;
    ok = write(fdout,buf,1);
    if(ok == -1)
    {
      err(3,"WRITE FAIL");
    } 
  }
}
// register an fd or get it
// call with -1 if you just want the fd
int fdaccept_register(int fd) {
  static int fdaccept = -1;
  if (fdaccept == -1 && fd != -1) {
    fdaccept = fd;
  }
  return fdaccept;
}
 
// signal handler for SIGINT
void sigint_handler(int sig) {
  (void)sig;
  int fd = fdaccept_register(-1);
  if (fd != -1)
    close(fd);
  _exit(0);
}
void* Work(void *arg)
{
	struct shared_queue *queue = arg;
	int file_connection;
	for(;;){
		file_connection = shared_queue_pop(queue);
		echo(file_connection, file_connection);
		close(file_connection);
  }
pthread_exit(NULL);	
}
void server(const char* portname)
{
	int info_err = 0;
  struct addrinfo hints,*resinfo = NULL;
	int connection; 
  int reuse_err;
  int reuse = 1;
	struct shared_queue *queue = new_shared_queue();
	int number =16;
  pthread_t thr[number]; 
  // setup hints and get local info
  memset(&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;                 // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;             // TCP
  hints.ai_protocol = 0;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // server mode
  // let's go !
  info_err = getaddrinfo(NULL, portname, &hints, &resinfo);
  // Error management
  if (info_err != 0) {
    errx(EXIT_FAILURE, "Server setup fails on port %s: %s", portname,
	 gai_strerror(info_err));
  }
	//for(answer=resinfo;answer!= NULL;answer=answer->ai_next){
	connection = socket(resinfo->ai_family,resinfo->ai_socktype,
											resinfo->ai_protocol);	
  reuse_err = setsockopt(connection, SOL_SOCKET, SO_REUSEADDR, &reuse, 
							sizeof (reuse));
  // Error management
  if (reuse_err == -1){
    err(EXIT_FAILURE, "Fail to set socket options");
		}
	int ok= fdaccept_register(connection);
	int True =bind(ok, resinfo->ai_addr,resinfo->ai_addrlen);
	freeaddrinfo(resinfo);
  if(True==-1)
	{
		errx(EXIT_FAILURE, "Couldn't connect");
	}
	listen(ok,5);
	size_t connect =0;
	for(;;){
	int fdcnx= accept(ok,NULL,NULL);
	if( fdcnx == -1)
		errx(3,"Fail");
	else
		connect++;
	shared_queue_push(queue,connect);
  int e = pthread_create(thr+connect-1,NULL,Work,queue);
	if(e!=0)
		errx(EXIT_FAILURE,"pthread_create()");
	}
	for(int j=0; j< number; j++)
	{
		int e = pthread_join(thr[j],NULL);
		if(e!=0)
			errx(EXIT_FAILURE,"pthread_join()");
  }

	close(ok);
	shared_queue_destroy(queue);
}


int main(int argc, char** argv)
{
	if(argc <2){
		printf("Arguments not here");
		return 0;
	}
	//SIGINT
	struct sigaction sigint;
  // Handle terminaison through Ctrl-C
  memset(&sigint, 0, sizeof (struct sigaction));
  sigint.sa_handler = sigint_handler;
  sigfillset(&sigint.sa_mask);
  sigint.sa_flags = SA_NODEFER;
  if ( sigaction(SIGINT, &sigint, NULL) == -1)
    err(EXIT_FAILURE, "can't change SIGINT behavior");

	//SIGCHLD
  struct sigaction sigchld;
  // Avoid zombies and don't get notify about children
  memset(&sigchld, 0, sizeof (struct sigaction));
  sigchld.sa_handler = SIG_DFL;
  sigemptyset(&sigchld.sa_mask);
  sigchld.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
  if ( sigaction(SIGCHLD, &sigchld, NULL) == -1 )
    err(EXIT_FAILURE, "can't change SIGCHLD behavior");
	server(argv[1]);
	return 0;
}
