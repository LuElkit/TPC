#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


char* build_query(const char *url, size_t *len)
{
	char *query= malloc(sizeof(char)*strlen(url)+20);
  strcpy(query, "GET ");
	strcat(query, url);
  strcat(query," HTTP/1.0\n\r\n\r");
  len= strlen(query);
 	return query;
	
}
void get_page(const char *name, const char *url, const char *port)
{
	struct addrinfo hints;
	struct addrinfo *result;
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
		connection=socket(answer->ai-family,answer->ai_socktype,answer->ai_protocol);
		if(connection == -1)continue;
		if(connect(connection,connection->ai_addr, connection->ai_addrlen)==0)break;
		close(connection);
	}
	freeaddrinfo(result);
	if(answer==NULL)
	{
		errx(EXIT_FAILURE, "Couldn't connect");
	}

	size_t len;
	char *query= build_query(url,&len);
	

}
int main(int argc, char** argv)
{
  if(argc < 2)
		return 0;
	size_t len;
  char *query= build_query(argv[1], &len);
  printf("chaine : %s, longueur: %zu",query,len);
  free(query);

	return 0;
}
