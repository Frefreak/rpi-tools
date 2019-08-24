#include <iostream>
#include <vector>
#include "pulses.hh"
#include <gpio.hh>
#include <time.h>

void replay(uint8_t pin, pulses sample)
{
  long long nanosec = static_cast<long long>(sample.interval * 1000);
  long nanos = 1e9;
  struct timespec ts = { static_cast<long>(nanosec / nanos),
                         static_cast<long>(nanosec % nanos)
                       };
  auto gpio = GPIO::GPIO();
  gpio.set_func(pin, GPIO::output);
  for (long long i = 0; i < sample.length; i++) {
    gpio.set_out(pin, sample.data[i]);
    nanosleep(&ts, NULL);
  }
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <pin> <file>\n";
    exit(EXIT_FAILURE);
  }
  uint8_t pin = atoi(argv[1]);
  FILE *fp = fopen(argv[2], "rb");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  pulses result;
  fread(&result.pin, 1, 1, fp);
  fread(&result.interval, sizeof(result.interval), 1, fp);
  fread(&result.length, sizeof(result.length), 1, fp);
  uint8_t *data = (uint8_t *)(malloc(result.length));
  if (data == NULL) {
    std::string info = std::string("malloc ") + std::to_string(result.length);
    perror(info.c_str());
    exit(EXIT_FAILURE);
  }
  fread(data, result.length, 1, fp);
  result.data = data;
  replay(pin, result);

  fclose(fp);
}
