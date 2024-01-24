CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
SRC=growing_arrays.c test_growing_arrays.c
OBJ=growing_arrays.o test_growing_arrays.o
HEADER=growing_arrays.h

growing_arrays: ${OBJ} 
	$(CC) $(OBJ) -o growing_arrays

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@
clean:
	rm -rf growing_arrays *.o

