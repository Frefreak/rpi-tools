#include "nec.hh"
#include "common.hh"
#include <numeric>

namespace NEC {
  void NEC::send_nec(uint8_t address, uint8_t command, int repeat) {
    std::vector<uint32_t> sequences = {LEADING_PULSE, LONG_PAUSE};
    for (int i = 0; i < 8; i++) {
      sequences.push_back(PREFIX);
      sequences.push_back((address >> i) & 0x1? ONE_SUFFIX : ZERO_SUFFIX);
    }
    for (int i = 0; i < 8; i++) {
      sequences.push_back(PREFIX);
      sequences.push_back((address >> i) & 0x1? ZERO_SUFFIX : ONE_SUFFIX);
    }
    for (int i = 0; i < 8; i++) {
      sequences.push_back(PREFIX);
      sequences.push_back((command >> i) & 0x1? ONE_SUFFIX : ZERO_SUFFIX);
    }
    for (int i = 0; i < 8; i++) {
      sequences.push_back(PREFIX);
      sequences.push_back((command>> i) & 0x1? ZERO_SUFFIX : ONE_SUFFIX);
    }
    sequences.push_back(PREFIX);

    if (repeat > 0) {
      int acc = accumulate(sequences.begin(), sequences.end(), 0);
      sequences.push_back(REPEAT_DIST - acc);
      sequences.push_back(LEADING_PULSE);
      sequences.push_back(SHORT_PAUSE);
      sequences.push_back(PREFIX);
      repeat--;
      acc = LEADING_PULSE + SHORT_PAUSE + PREFIX;
      while (repeat--) {
        sequences.push_back(REPEAT_DIST - acc);
        sequences.push_back(LEADING_PULSE);
        sequences.push_back(SHORT_PAUSE);
        sequences.push_back(PREFIX);
      }
    }


    for (int i = 1; i <= sequences.size(); i++) {
      gpio.set_out(pin, i % 2);
      timer.set_duration(sequences[i]);
      timer.do_delay();
    }
  }
}
