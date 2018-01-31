# define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include<err.h>
char* build_query(const char *url, size_t *len)
{
	char *query= malloc(sizeof(char)*strlen(url)+20);
  strcpy(query, "GET ");
	strcat(query, url);
  strcat(query," HTTP/1.0\n\r\n\r");
  *len = strlen(query);
 	return query;
	
}
void get_page(const char *name, const char *url, const char *port)
{
	struct addrinfo hints;
	struct addrinfo *result,*answer;
	int addrinfo_error;
  int connection;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
	addrinfo_error = getaddrinfo(name, port, &hints, &result);
  if ( addrinfo_error != 0 ) {
    errx(EXIT_FAILURE, "Fail getting address for %s on port %s: %s",
	 name, port, gai_strerror(addrinfo_error));
  }
	for(answer= result; answer !=NULL; answer= answer->ai_next)
	{
		connection=socket(answer->ai_family,answer->ai_socktype,answer->ai_protocol);
		if(connection == -1)continue;
		if(connect(connection,answer->ai_addr, answer->ai_addrlen)==0)break;
		close(connection);
	}
	freeaddrinfo(result);
	if(answer==NULL)
	{
		errx(EXIT_FAILURE, "Couldn't connect");
	}
  size_t len;
	char *query= build_query(url,&len);
	ssize_t ok= send(connection,query,len,0);
	if(ok==-1)
	{
		err(3,"Send of infos failed");
	}
	char donnees[len];
	ok= read(connection,donnees,len);
	ok= write(STDOUT_FILENO,donnees,len);
	close(connection);
	free(query);
 	ok= write(STDOUT_FILENO,"Connection by the server",25);

}
/*int main(int argc, char** argv)
{
  if(argc < 2)
		return 0;
	size_t len;
  char *query= build_query(argv[1], &len);
  printf("chaine : %s, longueur: %zu",query,len);
  free(query);

	return 0;
}*/
int main() {
  get_page("perdu.com", "http://perdu.com", "80");
  return 0;
}
