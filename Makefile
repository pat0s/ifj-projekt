EXECUTABLE = IFJ21
CFLAGS = -g -Wall -Wextra -Werror -lm

.PHONY = clean all

all: $(EXECUTABLE)

$(EXECUTABLE): scanner.o synAnalys.o #symtable.o
	gcc $(CFLAGS) $^ -o $@
	 


%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@



clean:
	rm  -f *.o