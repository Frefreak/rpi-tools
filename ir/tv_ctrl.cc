#include <nec.hh>
#include <string>
#include <iostream>
#include <vector>
#include <map>

/*
 * 电源: addr: 0x40, cmd: 0x12, rep: 1
 * 节目源: addr: 0x40, cmd: 0x14, rep: 0
 * up: addr: 0x40, cmd: 0x19, rep: 1
 * down: addr: 0x40, cmd: 0x1d, rep: 1
 * left: addr: 0x40, cmd: 0x46, rep: 4
 * right: addr: 0x40, cmd: 0x47, rep: 3
 * 确定: addr: 0x40, cmd: 0xa, rep: 1
 * 音量+: addr: 0x40, cmd: 0x1a, rep: 1
 * 音量-: addr: 0x40, cmd: 0x1e, rep: 1
*/


std::map<std::string, u_char> cmds = {
  {std::string("power"), 0x12},
  {std::string("source"), 0x14},
  {std::string("up"), 0x19},
  {std::string("down"), 0x1d},
  {std::string("left"), 0x46},
  {std::string("right"), 0x47},
  {std::string("confirm"), 0x0a},
  {std::string("volup"), 0x1a},
  {std::string("voldown"), 0x1e},
};

int main(int argc, char **argv)
{
  if (argc != 3 && argc != 4) {
    std::cout << "Usage: tv_ctrl <gpio pin> <cmd> [repeat]\n";
    exit(1);
  }
  int rep = -1;
  if (argc == 4) {
    rep = atoi(argv[3]);
  }

  if (cmds.find(argv[2]) != cmds.end()) {
    auto nec = NEC::NEC(atoi(argv[1]));
    if (rep != -1)
      nec.send_nec(0x40, cmds[argv[2]], rep);
    else
      nec.send_nec(0x40, cmds[argv[2]]);
  } else {
    std::cout << "command not found\n";
  }
  return 0;
}
