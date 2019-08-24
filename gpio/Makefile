UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	SO_EXT = .so
endif

ifeq ($(UNAME_S), Darwin)
	SO_EXT = .dylib
endif

all: libgpio$(SO_EXT) test

PWD = $(shell pwd)
CPPFLAGS := -I.
CFLAGS := -std=c++14 -Werror -Wall -Wpedantic -O3 -g
LDFLAGS := -Wl,-rpath,$(PWD),-L.,-lgpio

libgpio$(SO_EXT): gpio.hh gpio.cc
	g++ $(CPPFLAGS) $(CFLAGS) gpio.cc -shared -o $@

test: libgpio$(SO_EXT) test.cc
	g++ $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) test.cc -o test

.PHONY: clean

clean:
	rm -rf libgpio$(SO_EXT) test
