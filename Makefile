EXECUTABLE = IFJ21
CFLAGS = -std=c99 -pedantic -g -Wall -Wextra -Werror -lm

.PHONY = clean all tests our_tests

all: $(EXECUTABLE)

$(EXECUTABLE):  synAnalys.o  scanner.o symtable.o expressions.o expressions_stack.o code_generator.o
	gcc $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

our_tests: 
	chmod +x run_test.sh
	./run_test.sh IFJ21 yes

test:
	cd tests/ifjtest && ./ifjtest

clean:
	rm $(EXECUTABLE) *.o

