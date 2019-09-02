#include <nec.hh>
#include <iostream>

int main(void)
{
  auto nec = NEC::NEC_RECV(24);
  auto result = nec.recv_nec_custom(3000000);
  for (auto t: result)
    std::cout << t << ' ';
  std::cout << '\n';

  getchar();

  auto nec2 = NEC::NEC(21);
  nec2.send_nec_custom(result);

  return 0;
}
