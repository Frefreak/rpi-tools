#include <iostream>
#include <string>
#include <cstdint>
#include <YBOF2.cc>

struct Arg {
  u_char ce;
  std::string conf_fp = ".config/ac_ctrl.yaml";
};

void read_conf(Arg &arg)
{
  //std::cout << arg.conf_fp << '\n';
}

void do_cmd_power(CLI::App *cmd, Arg &arg)
{
  YBOF2 remote;
  std::string s;
  cmd->get_option("status")->results(s);
  if (s == "on")
    remote.power = 1;
  else
    remote.power = 0;
  auto p = remote.encode();
  std::cout << std::get<0>(p) << ' ' << std::get<1>(p) << '\n';
}

void do_cmd_version()
{
  std::cout << "I have no version.\n";
}

int main(int argc, char *argv[])
{
  CLI::App app{"AC Controller"};

  Arg arg = Arg();

  app.add_option("-p,--pin", arg.ce, "CE PIN used in RF24 lib");
  app.add_option("-c,--conf", arg.conf_fp, "config file");

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
