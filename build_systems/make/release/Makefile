VPATH := ../../..
CFLAGS += -O3

.PHONY: all clean

all: tests libvector.a

tests: libvector.a tests.o
	$(CC) $(CFLAGS) $^ -o $@

libvector.a: vector.o vector_system.o
	ar rcs $@ $^

clean:
	rm -f *.o *.a tests
