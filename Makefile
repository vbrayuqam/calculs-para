CC = gcc
CCOPT = -Wall -g -O2 -march=native
LD = gcc
LDOPT =  -Wall -g -O2 -march=native

EXEC = vec_matrix

all: $(EXEC)

vec_matrix: matrices.o vec_matrix.o scalvec.o matmult.o
	$(LD) $(LDOPT) -o $@ $^

%.o: %.c
	$(CC) $(CCOPT) -o $@ -c $< 

clean:
	rm -f *.o $(EXEC)

.PHONY: clean
