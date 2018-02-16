# Makefile
 
CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =
 
OBJ = echo_server.o
DEP = ${OBJ:.o=.d}
 
all:  echo_server
 
echo_server: ${OBJ}
 
.PHONY: clean
 
clean:
	${RM} ${OBJ} ${DEP}  echo_server
 
-include ${DEP}
 
# END
