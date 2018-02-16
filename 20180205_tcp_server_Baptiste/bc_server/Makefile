# Makefile
 
CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =
 
OBJ = bc_server.o
DEP = ${OBJ:.o=.d}
 
all: bc_server
 
bc_server: ${OBJ}
 
.PHONY: clean
 
clean:
	${RM} ${OBJ} ${DEP} bc_server
 
-include ${DEP}
 
# END
