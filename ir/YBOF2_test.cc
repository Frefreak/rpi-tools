#include <iostream>
#include "YBOF2.cc"

int main(void)
{
  auto remote = YBOF2();
  // remote.power = 1;
  remote.temp = 26 - 16;
  auto p = remote.encode();
  std::cout << std::get<0>(p) << ' ' <<  std::get<1>(p) << '\n';

  char buffer[9];
  remote.encode_b(buffer);
  std::cout << '[';
  for (auto ch: buffer) {
    std::cout << "0x" << std::hex << +ch << ", ";
  }
  std::cout << "]\n";
  return 0;
}
