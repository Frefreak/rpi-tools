#include <iostream>
#include <gpio.hh>
#include <unistd.h>

int main(int argc, char *argv[])
{
  auto gpio = GPIO::GPIO();
  int o = 1;
  while (1) {
    std::cout<< gpio.get(12) << std::endl;
    gpio.set_out(12, o);
    o ^= 1;
    usleep(500000);
  }

  return 0;
}
