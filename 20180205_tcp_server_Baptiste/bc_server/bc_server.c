# define _XOPEN_SOURCE 700

# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <err.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
# include <sys/wait.h>

# include <errno.h>

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

void echo(int fdin, int fdout) {
  char buf[1];
  int r, w;
  while ((r = read(fdin, buf, 1))) {
    if (r != -1 || errno == EINTR || errno == EAGAIN
        || errno == EWOULDBLOCK) {
      w = write(fdout, buf, 1);
      if (w == -1 && !(errno == EINTR || errno == EAGAIN
          || errno == EWOULDBLOCK))
        errx(errno, "Can't writing");
    } else { errx(errno, "Can't reading"); }
  }
  /*if (r == -1 && !(errno == EINTR || errno == EAGAIN
      || errno == EWOULDBLOCK))
    errx(errno, "Can't reading");*/
}

void server(const char *portname) {
  // Server-side socket
  int info_err = 0;
  struct addrinfo hints, *resinfo = NULL;
 
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

  // Connection for each result
  int cnx = socket(resinfo->ai_family, resinfo->ai_socktype, resinfo->ai_protocol);
  if (cnx == -1) errx(errno, "Can't create the socket");
  
  if (!resinfo) errx(EXIT_FAILURE, "Couldn't connect");
  //freeaddrinfo(resinfo);

  // Set the option SOL_REUSEADDR
  int reuse_err;
  int reuse = 1;
  reuse_err = setsockopt(cnx, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof (reuse));
 
  // Error management
  if (reuse_err == -1)
    err(EXIT_FAILURE, "Fail to set socket options");

  int fdaccept = fdaccept_register(cnx);
  close(cnx);
  
  struct sockaddr_in server, client;
  memset(&server, 0, sizeof(server));
  socklen_t client_size; 

  int b = bind(fdaccept, (struct sockaddr *) &server, sizeof(server));
  if (b == -1) errx(errno, "Can't bind");

  int l = listen(fdaccept, 5);
  if (l == -1) errx(errno, "Can't listen");

  int fdcnx;
  for (;;) {
    client_size = sizeof(struct sockaddr);
    if ((fdcnx = accept(fdaccept, (struct sockaddr *) &client, &client_size)) == -1)
      errx(errno, "Can't accept");

    if (fork()){
      close(fdcnx);
      wait(NULL);
      continue;   
    } else {
      close(fdaccept);
      echo(fdcnx, fdcnx);
      close(fdcnx);
    }
    //echo(fdcnx, fdcnx);
    close(fdcnx);
  }
  close(fdaccept);
}

int main(int argc, char const *argv[]) {
  
  if (argc < 2)
    errx(1, "Missing arguments");
  else if (argc > 2)
    errx(1, "Too much arguments");
  // SIGINT
  struct sigaction sigint;
 
  // Handle terminaison through Ctrl-C
  memset(&sigint, 0, sizeof (struct sigaction));
  sigint.sa_handler = sigint_handler;
  sigfillset(&sigint.sa_mask);
  sigint.sa_flags = SA_NODEFER;
  if ( sigaction(SIGINT, &sigint, NULL) == -1)
    err(EXIT_FAILURE, "can't change SIGINT behavior");
  
  // SIGCHLD
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