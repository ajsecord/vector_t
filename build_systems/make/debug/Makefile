VPATH := ../../..
CFLAGS += -O0 -g

.PHONY: all clean

all: tests libvector.a

tests: tests.o libvector.a
	$(CC) $(CFLAGS) -coverage $^ -o $@

libvector.a: CFLAGS += -coverage
libvector.a: vector.o vector_system.o
	ar rcs $@ $^

clean:
	rm -f *.o *.a *.gcda *.gcno tests 
	rm -rf *.dSYM
