CC=gcc
CFLAGS=-I.

DEPS = floodfill.h 
OBJ = floodfill.o explore_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
test_run : $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
clean:
	rm -rf *o test_run
