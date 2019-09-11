#include <iostream>
#include <vector>
#include "pulses.hh"
#include <gpio.hh>
#include <timer.hh>

void replay(uint8_t pin, pulses sample)
{
  auto timer = Timer::Timer();
  timer.set_duration(sample.interval);

  auto gpio = GPIO::GPIO();
  gpio.set_func(pin, GPIO::output);
  for (unsigned long i = 0; i < sample.length; i++) {
    gpio.set_out(pin, sample.data[i]);
    timer.do_delay();
  }
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <pin> <file>\n";
    exit(EXIT_FAILURE);
  }
  uint8_t pin = atoi(argv[1]);
  pulses_t result = read_pulses(argv[2]);
  replay(pin, result);
}
