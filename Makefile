
CFLAGS=-Wall -Werror
tests: tests.o vector.o
	$(CC) $(CFLAGS) -o tests tests.o vector.o

clean:
	rm -f *.o tests
