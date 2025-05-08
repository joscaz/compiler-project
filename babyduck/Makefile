CC = gcc
CFLAGS = -Wall

all: babyduck

babyduck: lex.yy.c parser.tab.c semantic_cube.c semantic_structures.c
	$(CC) $(CFLAGS) -o babyduck lex.yy.c parser.tab.c semantic_cube.c semantic_structures.c -ly

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

clean:
	rm -f babyduck parser.tab.c parser.tab.h lex.yy.c