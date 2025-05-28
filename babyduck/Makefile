CC = gcc
CFLAGS = -Wall -g

OBJS = parser.tab.o lex.yy.o semantic_structures.o semantic_cube.o virtual_memory.o quadruple.o stack.o constant_table.o quadruple_generator.o virtual_machine.o

all: babyduck

babyduck: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

semantic_structures.o: semantic_structures.c semantic_structures.h datatype.h
	$(CC) $(CFLAGS) -c semantic_structures.c

semantic_cube.o: semantic_cube.c semantic_cube.h datatype.h
	$(CC) $(CFLAGS) -c semantic_cube.c

virtual_memory.o: virtual_memory.c virtual_memory.h datatype.h
	$(CC) $(CFLAGS) -c virtual_memory.c

quadruple.o: quadruple.c quadruple.h datatype.h virtual_memory.h
	$(CC) $(CFLAGS) -c quadruple.c

stack.o: stack.c stack.h datatype.h quadruple.h
	$(CC) $(CFLAGS) -c stack.c

constant_table.o: constant_table.c constant_table.h datatype.h virtual_memory.h
	$(CC) $(CFLAGS) -c constant_table.c

quadruple_generator.o: quadruple_generator.c quadruple_generator.h stack.h quadruple.h constant_table.h virtual_memory.h semantic_structures.h
	$(CC) $(CFLAGS) -c quadruple_generator.c

virtual_machine.o: virtual_machine.c virtual_machine.h quadruple.h constant_table.h semantic_structures.h
	$(CC) $(CFLAGS) -c virtual_machine.c

clean:
	rm -f babyduck $(OBJS) parser.tab.c parser.tab.h lex.yy.c