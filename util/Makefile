MATPLOTLIB_CPP_DIR = ../matplotlib-cpp
NUMPY_DIR = $(shell python3.7 -c "import numpy; import os; print(os.path.dirname(numpy.__file__))")

MATPLOTLIB_CPP_FLAGS = $(shell pkg-config python3 --cflags --libs)
MATPLOTLIB_CPP_FLAGS += -I$(MATPLOTLIB_CPP_DIR)
MATPLOTLIB_CPP_FLAGS += -I$(NUMPY_DIR)/core/include

GPIO_DIR = $(shell pwd)/../gpio
GPIO_FLAGS = -I$(GPIO_DIR) -L$(GPIO_DIR) -lgpio -Wl,-rpath,$(GPIO_DIR)

CFLAGS = -std=c++14 -O3

all: test_matplotlib receiver replay

test_matplotlib: test_matplotlib.cc
	g++ $< $(CFLAGS) $(MATPLOTLIB_CPP_FLAGS) -o $@

receiver: receiver.cc pulses.hh
	g++ $< $(CFLAGS) $(GPIO_FLAGS) -o $@

replay: replay.cc pulses.hh
	g++ $< $(CFLAGS) $(GPIO_FLAGS) -o $@

.PHONY: clean

clean:
	rm -rf test_matplotlib
