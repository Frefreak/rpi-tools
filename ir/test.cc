#include <nec.hh>
#include <iostream>

int main(void)
{
  auto nec = NEC::NEC(21);
  nec.send_nec(0x40, 0xBF);
  return 0;
}
