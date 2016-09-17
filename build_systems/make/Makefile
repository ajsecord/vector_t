.PHONY: all clean

export CFLAGS := -std=c99 -Wall -Werror

all:
	$(MAKE) -C debug
	$(MAKE) -C release

clean:
	$(MAKE) -C debug clean
	$(MAKE) -C release clean
