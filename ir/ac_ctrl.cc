#include <iostream>
#include <string>
#include <cstdint>
#include <YBOF2.cc>

struct Arg {
  u_char ce = 21;
  std::string conf_fp = ".config/ac_ctrl.yaml";
  uint64_t dest_addr = 0x65646f4e32;
  u_char mask = 0b10101010;
};

void read_conf(Arg &arg)
{
  //std::cout << arg.conf_fp << '\n';
}

#ifdef USE_RF24

void send_to_arduino(YBOF2 remote, Arg &arg)
{
  char buffer[9];
  remote.encode_b(buffer);
  for (auto &ch: buffer)
    ch = ch ^ arg.mask;

  RF24 radio(arg.ce, 0);
  radio.begin();
  radio.setRetries(15, 15);
  radio.setChannel(120);
  radio.openWritingPipe(arg.dest_addr);

  radio.write(buffer, sizeof(buffer));
}

#else

void send_to_arduino(YBOF2 remote, Arg &arg)
{
  std::cout << "RF24 library not found, mimicking...\n";
  auto p = remote.encode();
  std::cout << std::get<0>(p) << ' ' << std::get<1>(p) << '\n';

  std::cout << "ce: " << static_cast<int>(arg.ce) << std::endl;
  std::cout << "conf_fp" << arg.conf_fp << std::endl;
  std::cout << "dest_addr: " << std::hex << arg.dest_addr << std::endl;
  std::cout << "mask: " << std::hex << static_cast<int>(arg.mask) << std::endl;
}

#endif

void do_cmd_power(CLI::App *cmd, Arg &arg)
{
  YBOF2 remote;
  std::string s;
  cmd->get_option("status")->results(s);
  if (s == "on")
    remote.power = 1;
  else
    remote.power = 0;


  send_to_arduino(remote, arg);
}

void do_cmd_version()
{
  std::cout << "I have no version.\n";
}

int main(int argc, char *argv[])
{
  CLI::App app{"AC Controller"};

  Arg arg = Arg();

  app.add_option("-p,--pin", arg.ce, "CE PIN used in RF24 lib (default: 21)");
  app.add_option("-c,--conf", arg.conf_fp, "config file");
  app.add_option("-d,--dest", arg.dest_addr, "RF24 destination address");
  app.add_option("-m,--mask", arg.mask, "xor mask when sending via RF24");

  app.parse_complete_callback([&arg] { read_conf(arg); });

  CLI::App *power_cmd = app.add_subcommand("power", "turn AC on or off");
  power_cmd->add_option("status", "on or off")->required()->check(CLI::IsMember({"on", "off"}));
  power_cmd->final_callback([power_cmd, &arg] { do_cmd_power(power_cmd, arg); });


  auto version_cmd = app.add_subcommand("version", "report version");
  version_cmd->final_callback([] { do_cmd_version(); });

  app.require_subcommand(1);

  CLI11_PARSE(app, argc, argv);

  return 0;
}
