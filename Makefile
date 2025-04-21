CC = g++
MPI_CC = mpic++
FLAGS = -Wall -pedantic -std=c++11

all: multigrep_mpi.out multigrep_seq.out multigrep_omp.out

multigrep_mpi.out: multigrep_mpi.o mg_structures.o
	$(MPI_CC) $(FLAGS) multigrep_mpi.o mg_structures.o -o multigrep_mpi.out

multigrep_seq.out: multigrep_seq.o mg_structures.o
	$(CC) $(FLAGS) multigrep_seq.o mg_structures.o -o multigrep_seq.out

multigrep_mpi.o: multigrep_mpi.cpp
	$(MPI_CC) $(FLAGS) -c multigrep_mpi.cpp -o multigrep_mpi.o

multigrep_seq.o: multigrep_seq.cpp
	$(CC) $(FLAGS) -c multigrep_seq.cpp -o multigrep_seq.o

multigrep_omp.out: multigrep_omp.o mg_structures.o
	$(CC) $(FLAGS) -fopenmp multigrep_omp.o mg_structures.o -o multigrep_omp.out

multigrep_omp.o: multigrep_omp.cpp
	$(CC) $(FLAGS) -fopenmp -c multigrep_omp.cpp -o multigrep_omp.o

mg_structures.o: mg_structures.hpp mg_structures.cpp
	$(CC) $(FLAGS) -c mg_structures.cpp -o mg_structures.o

mg_gdb.out: multigrep_seq.cpp mg_structures.hpp mg_structures.cpp
	$(CC) $(FLAGS) -g -c multigrep_seq.cpp -o multigrep_seq.gdb.o
	$(CC) $(FLAGS) -g -c mg_structures.cpp -o mg_structures.gdb.o
	$(CC) $(FLAGS) -g multigrep_seq.gdb.o mg_structures.gdb.o -o mg_gdb.out

clean:
	rm -f *.o *.out
