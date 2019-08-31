UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	SO_EXT = .so
	LIB_FLAGS =
endif

ifeq ($(UNAME_S), Darwin)
	SO_EXT = .dylib
	LIB_FLAGS = -install_name @rpath/libgpio.dylib
endif

all: libtimer$(SO_EXT)

PWD = $(shell pwd)
CPPFLAGS := -I.
CFLAGS := -std=c++14 -Werror -Wall -Wpedantic -O3 -g
LDFLAGS := -Wl,-rpath,$(PWD),-L.,-ltimer

libtimer$(SO_EXT): timer.hh timer.cc
	g++ $(CPPFLAGS) $(CFLAGS) $(LIB_FLAGS) timer.cc -shared -o $@

test: libtimer$(SO_EXT) test.cc
	g++ $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) test.cc -o test

.PHONY: clean

clean:
	rm -rf libtimer$(SO_EXT) test
