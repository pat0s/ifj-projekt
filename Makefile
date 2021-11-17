EXECUTABLE = main
CFLAGS = -g -Wall -Wextra --std=c99

.PHONY = clean all


$(EXECUTABLE): scanner.o synAnalys.o
	gcc $(CFLAGS) -o $@ $^ 

scanner.o: scanner.c error.h
	gcc $(CFLAGS) -c $<

symtable.o: symtable.c error.h
	gcc $(CFLAGS) -c $<

synAnalys.o: synAnalys.c error.h
	gcc $(CFLAGS) -c $<


clean:
	rm  -f *.o