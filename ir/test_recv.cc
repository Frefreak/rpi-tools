#include <nec.hh>
#include <iostream>

int main(void)
{
  auto nec = NEC::NEC_RECV(24);
  bool ok = nec.wait_for_leader(3000000);
  std::cout << ok << '\n';
  return 0;
}
