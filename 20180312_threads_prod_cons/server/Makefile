#Makefile
 
CC=gcc -pthread -fsanitize=address
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -Og
LDFLAGS=
LDLIBS=
 
SRC= ../queue/shared_queue.c server.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
 
all: server
 
server: ${OBJ}
 
clean:
	rm -f ${OBJ}
	rm -f ${DEP}
	rm -f server
 
-include ${DEP}
 
# END

