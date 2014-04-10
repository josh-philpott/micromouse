CC=gcc
CFLAGS=-I.

DEPS = floodfill.h numstack.h
OBJ = floodfill.o numstack.o explore_test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
test_run : $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
clean:
	rm -rf *o test_run
