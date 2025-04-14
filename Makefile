CC = g++
FLAGS = -Wall -pedantic -ansi

multigrep.out: multigrep.o mg_structures.o
	$(CC) $(FLAGS) multigrep.o mg_structures.o -o multigrep.out

multigrep.o: multigrep.cpp
	$(CC) $(FLAGS) -c multigrep.cpp -o multigrep.o

mg_structures.o: mg_structures.hpp mg_structures.cpp
	$(CC) $(FLAGS) -c mg_structures.cpp -o mg_structures.o

mg_gdb.out: multigrep.cpp mg_structures.hpp mg_structures.cpp
	$(CC) $(FLAGS) -g -c multigrep.cpp -o multigrep.gdb.o
	$(CC) $(FLAGS) -g -c mg_structures.cpp -o mg_structures.gdb.o
	$(CC) $(FLAGS) -g multigrep.gdb.o mg_structures.gdb.o -o mg_gdb.out

clean:
	rm -f *.o *.out