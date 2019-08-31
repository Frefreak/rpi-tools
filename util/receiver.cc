#include <iostream>
#include "pulses.hh"
#include <gpio.hh>
#include <timer.hh>


// no overflow checks, interval should be small enough
// interval is in micro second, duration in second
pulses sample(uint8_t pin, uint32_t interval, float duration)
{
  long long nanosec = static_cast<long long>(interval * 1000);
  uint64_t iter = duration / interval * 100000 + 1;
  auto gpio = GPIO::GPIO();

  uint8_t *data = (uint8_t *)(malloc(iter));
  if (data == NULL) {
    std::string info = std::string("malloc ") + std::to_string(iter);
    perror(info.c_str());
    exit(EXIT_FAILURE);
  }
  gpio.set_func(pin, GPIO::input);

  auto timer = Timer::Timer();
  timer.set_duration(duration);
  for (long long i = 0; i < iter; i++) {
    data[i] = gpio.get(pin);
    timer.do_delay();
  }
  return pulses{pin, interval, iter, data};
}

int main(int argc, char **argv)
{
  if (argc != 5) {
    std::cout << "Usage: " << argv[0] <<
      " <pin> <interval in microsec> <duration in seconds> <output>\n";
    exit(EXIT_FAILURE);
  }
  uint8_t pin = atoi(argv[1]);
  uint32_t interval = atol(argv[2]);
  float duration = atof(argv[3]);
  std::cout << "capturing...\n";
  pulses_t result = sample(pin, interval, duration);
  write_pulses(result, argv[4]);
}
