#include <iostream>
#include <gpio.hh>

int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <pin> <0 or 1>\n";
    exit(1);
  }
  int pin = atoi(argv[1]);
  int st = atoi(argv[2]);
  auto gpio = GPIO::GPIO();
  gpio.set_func(pin, GPIO::output);
  gpio.set_out(pin, st);
  // std::cout << (uint32_t)gpio.get(pin) << std::endl;
  return 0;
}
