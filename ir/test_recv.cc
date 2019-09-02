#include <nec.hh>
#include <iostream>

int main(void)
{
  auto nec = NEC::NEC_RECV(24);
  auto result = nec.recv_nec_custom(3000000);
  for (auto t: result)
    std::cout << t << ' ';
  std::cout << '\n';
  return 0;
}
