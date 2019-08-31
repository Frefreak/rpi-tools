#include <iostream>
#include "pulses.hh"
#include <gpio.hh>
#include <time.h>


// no overflow checks, interval should be small enough
// interval is in micro second, duration in second
pulses sample(uint8_t pin, float interval, float duration)
{
  long long nanosec = static_cast<long long>(interval * 1000);
  uint64_t iter = duration / interval * 100000 + 1;
  auto gpio = GPIO::GPIO();

  long nanos = 1e9;
  struct timespec ts = { static_cast<long>(nanosec / nanos),
                         static_cast<long>(nanosec % nanos)
                       };
  uint8_t *data = (uint8_t *)(malloc(iter));
  if (data == NULL) {
    std::string info = std::string("malloc ") + std::to_string(iter);
    perror(info.c_str());
    exit(EXIT_FAILURE);
  }
  gpio.set_func(pin, GPIO::input);
  for (long long i = 0; i < iter; i++) {
    data[i] = gpio.get(pin);
    nanosleep(&ts, NULL);
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
  float interval = atof(argv[2]);
  float duration = atof(argv[3]);
  std::cout << "capturing...\n";
  pulses result = sample(pin, interval, duration);
  FILE *fp = fopen(argv[4], "wb");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  std::cout << "data length: " << result.length << "\n";
  std::cout << "total length: " << 13 + result.length << "\n";
  std::cout << "writing...\n";
  fwrite(&result.pin, sizeof(result.pin), 1, fp);
  fwrite(&result.interval, sizeof(result.interval), 1, fp);
  fwrite(&result.length, sizeof(result.length), 1, fp);
  fwrite(result.data, result.length, 1, fp);
  fclose(fp);
}
