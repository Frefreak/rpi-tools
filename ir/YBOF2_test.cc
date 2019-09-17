#include <iostream>
#include "YBOF2.cc"

int main(void)
{
  auto remote = YBOF2();
  // remote.power = 1;
  remote.temp = 26 - 16;
  auto p = remote.encode();
  std::cout << std::get<0>(p) << ' ' <<  std::get<1>(p) << '\n';
  return 0;
}
