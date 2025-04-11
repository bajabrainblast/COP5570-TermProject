CC = g++
FLAGS = -Wall -pedantic -ansi

multigrep.out: multigrep.cpp
	$(CC) $(FLAGS) multigrep.cpp -o multigrep.out

clean:
	rm -f *.o *.out