EXECUTABLE = IFJ21
CFLAGS = -std=c99 -pedantic -g -Wall -Wextra -lm #-Wextra -Werror -lm

.PHONY = clean all

all: $(EXECUTABLE)

$(EXECUTABLE):  synAnalys.o  scanner.o symtable.o expressions.o expressions_stack.o code_generator.o
	gcc $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

test: 
	./run_test.sh IFJ21 yes

clean:
	rm $(EXECUTABLE) *.o

exp: scanner.o symtable.o expressions.o expressions_stack.o
	gcc $(CFLAGS) $^ -o $@
expc: 
	rm exp

# potom vymazat
symtable:
	gcc -std=c99 -Wall -pedantic -g symtable.c -o symtable

code_generator:
	gcc -std=c99 -Wall -pedantic -g code_generator.c -o code_generator
