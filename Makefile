SOURCES=vector.c vector_system.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-std=c99 -Wall -Werror -O0 -g
tests: tests.o libvector.a
	$(CC) $(CFLAGS) $^ -o $@

libvector.a: $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f tests libvector.a $(OBJECTS)
