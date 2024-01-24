CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
SRC=test_ll_cycle.c ll_cycle.c
OBJ=test_ll_cycle.o ll_cycle.o
HEADER=ll_cycle.c

check_cycle: ${OBJ} ${HEADER}
	$(CC) $(OBJ) -o check_cycle
    
%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

clean:
	rm -rf check_cycle
	rm -rf *.o


