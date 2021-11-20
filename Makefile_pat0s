EXECUTABLE = main
CFLAGS = -g -Wall -Wextra -Werror --std=c99

.PHONY = clean


$(EXECUTABLE): scanner.o
	gcc $(CFLAGS) -o $@ $^ 

scanner.o: scanner.c scanner.h
	gcc $(CFLAGS) -c $<


clean:
	rm  -f *.o