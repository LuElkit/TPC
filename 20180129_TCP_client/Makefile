# Makefile
 
CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =
 
OBJ = get_page.o
DEP = ${OBJ:.o=.d}
 
all: get_page
 
get_page: ${OBJ}
 
.PHONY: clean
 
clean:
	${RM} ${OBJ} ${DEP} get_page
 
-include ${DEP}
 
# END
