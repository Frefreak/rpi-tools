#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <cstdint>
#include <gpio.hh>
#include <timer.hh>

int main(int argc, char **argv)
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <pin> <period in microseconds>\n", argv[0]);
    exit(1);
  }
  int pin = atoi(argv[1]);
  unsigned long period = atol(argv[2]);
  auto timer = Timer::Timer();
  timer.set_duration(period / 2);
  auto gpio = GPIO::GPIO();

  gpio.set_func(pin, GPIO::output);
  while (1) {
    gpio.set_out(pin, 1);
    timer.do_delay();
    gpio.set_out(pin, 0);
    timer.do_delay();
  }
  return 0;
}
