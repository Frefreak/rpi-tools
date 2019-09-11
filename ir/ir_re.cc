#include <nec.hh>
#include <iostream>
#include <vector>

extern std::string decode(std::vector<uint32_t> &seqs);

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <gpio pin>\n";
    exit(1);
  }

  auto nec = NEC::NEC_RECV(atoi(argv[1]));
  std::cout << "ir code reverse engineering helper\n";
  std::cout << "type the code name (desc) and press the button:\n";
  std::string desc;
  while (1) {
    std::cout << "code desc: ";
    std::cin >> desc;
    auto result = nec.recv_nec_custom(6000000);
    std::cout << desc << ": " << decode(result) << '\n';
  }
  return 0;
}
