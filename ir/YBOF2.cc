#include <cstdint>
#include <string>
#include <utility>
#include <tuple>

using u32 = uint32_t;
const u32 cfixed1 = 0b0100101000;
const u32 cfixed2 = 0b000;
const u32 cfixed3 = 0b000;
const u32 cfixed4 = 0b0000000000001000;
const u32 cfixed5 = 0b0;

struct YBOF2 {
  YBOF2(): mode(0b001), power(0), wind(0b01), sweep(0), sleep(0), temp(0b1010),
           timer(0), strong(0), light(1), health(0), dry(0), air(0), fixed1(cfixed1),
           ud_swp(0), fixed2(cfixed2), lr_swp(0), fixed3(cfixed3), temp_display(0),
           fixed4(cfixed4), pwr_save(0), fixed5(cfixed5) {}
  u32 mode  : 3;
  u32 power : 1;
  u32 wind  : 2;
  u32 sweep : 1;
  u32 sleep : 1;
  u32 temp  : 4;
  u32 timer : 8;
  u32 strong: 1;
  u32 light : 1;
  u32 health: 1;
  u32 dry   : 1;
  u32 air   : 1;
  u32 fixed1: 10;

  u32 ud_swp: 1;
  u32 fixed2: 3;
  u32 lr_swp: 1;
  u32 fixed3: 3;
  u32 temp_display: 2;
  u32 fixed4: 16;
  u32 pwr_save: 1;
  u32 fixed5: 1;


  void decode(std::string pre, std::string post) {
    ;
  }

  inline std::string bit2ch(u32 val, u32 len) {
    std::string s = "";
    while (len--) {
      s += (val & 0x1)? "1": "0";
      val >>= 1;
    }
    return s;
  }

  std::tuple<std::string, std::string> encode(void) {
    std::string pre = "";
    std::string post = "";

    pre += bit2ch(mode, 3);
    pre += bit2ch(power, 1);
    pre += bit2ch(wind, 2);
    pre += bit2ch(sweep, 1);
    pre += bit2ch(sleep, 1);
    pre += bit2ch(temp, 4);
    pre += bit2ch(timer, 8);
    pre += bit2ch(strong, 1);
    pre += bit2ch(light, 1);
    pre += bit2ch(health, 1);
    pre += bit2ch(dry, 1);
    pre += bit2ch(air, 1);
    pre += bit2ch(fixed1, 10);

    post += bit2ch(ud_swp, 1);
    post += bit2ch(fixed2, 3);
    post += bit2ch(lr_swp, 1);
    post += bit2ch(fixed3, 3);
    post += bit2ch(temp_display, 2);
    post += bit2ch(fixed4, 16);
    post += bit2ch(pwr_save, 1);
    post += bit2ch(fixed5, 1);

    //http://www.zanks.cn/blog/ac-controller/gree-ac.html
    u32 checksum = (mode - 1) + temp + 5 + lr_swp + air + pwr_save;
    if (power == 0)
      checksum ^= 1 << 3;
    post += bit2ch(checksum, 4);

    return std::make_pair(pre, post);
  }
};
