UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	SO_EXT = .so
	LIB_FLAGS =
endif

ifeq ($(UNAME_S), Darwin)
	SO_EXT = .dylib
	LIB_FLAGS = -install_name @rpath/libir.dylib
endif

all: libir$(SO_EXT)

GPIO_DIR = $(shell pwd)/../gpio
GPIO_FLAGS = -I$(GPIO_DIR) -L$(GPIO_DIR) -lgpio -Wl,-rpath,$(GPIO_DIR)
ifeq ($(UNAME_S), Linux)
	GPIO_FLAGS += -Wl,--enable-new-dtags
endif

TIMER_DIR = $(shell pwd)/../timer
TIMER_FLAGS = -I$(TIMER_DIR) -L$(TIMER_DIR) -ltimer -Wl,-rpath,$(TIMER_DIR)
ifeq ($(UNAME_S), Linux)
	TIMER_FLAGS += -Wl,--enable-new-dtags
endif

PWD = $(shell pwd)
CPPFLAGS := -I.
CFLAGS := -std=c++14 -Werror -Wall -Wpedantic -O3 -g
LDFLAGS := -Wl,-rpath,$(PWD),-L.,-lir

libir$(SO_EXT): nec.hh nec.cc common.hh
	g++ $(CPPFLAGS) $(CFLAGS) $(LIB_FLAGS) $(GPIO_FLAGS) $(TIMER_FLAGS) \
		nec.cc -shared -o $@

test: test.cc libir$(SO_EXT)
	g++ $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(GPIO_FLAGS) $(TIMER_FLAGS) \
		test.cc -lir -o test

.PHONY: clean

clean:
	rm -rf libir$(SO_EXT) test
