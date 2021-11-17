EXECUTABLE = main
CFLAGS = -g -Wall -Wextra  --std=c99

.PHONY = clean all


$(EXECUTABLE): scanner.o synAnalys.o
	gcc $(CFLAGS) -o $@ $^ 

scanner.o: scanner.c scanner.h error.h 
	gcc $(CFLAGS) -c $<

#Nedavam, lebo je tam nejaky erro a teraz to nie je dolezite
#symtable.o: symtable.c error.h
#	gcc $(CFLAGS) -c $<

synAnalys.o: synAnalys.c synAnalys.h error.h 
	gcc $(CFLAGS) -c $<


clean:
	rm  -f *.o