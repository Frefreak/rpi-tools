#include "nec.hh"
#include <numeric>
#include <cmath>

namespace NEC {
  std::vector<segment> NEC::modulate(std::vector<uint32_t> &seqs)
  {
    std::vector<segment> segs = std::vector<segment>();
    float period = 1000000. / carrier_freq;
    int duty = round(period / 4);
    int no_duty = round(period - duty);
    for (unsigned int i = 1; i <= seqs.size(); i++) {
      if (i % 2) { // 1, modulate to carrier wave
        int cycle = round(seqs[i - 1] / period);
        for (int j = 0; j < cycle; j++) {
          segs.push_back(mk_seg(duty, 1));
          segs.push_back(mk_seg(no_duty, 0));
        }

      } else { // 0, just wait
        segs.push_back(mk_seg(seqs[i - 1], 0));
      }
    }

    return segs;
  }

  void NEC::add_repeat_code(std::vector<uint32_t> &sequences, int repeat) {
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
  }

  void NEC::send_nec_custom(std::vector<uint32_t> &sequences) {
    gpio->set_out(pin, 0);
    auto segs = modulate(sequences);
    for (segment seg: segs) {
      if (seg.level)
        gpio->set_out(pin, 1);
      else
        gpio->set_out(pin, 0);
      timer->set_duration(seg.duration);
      timer->do_delay();
    }
    gpio->set_out(pin, 0);
  }

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

    add_repeat_code(sequences, repeat);
    send_nec_custom(sequences);
  }

  // almost identical to send_nec
  void NEC::send_nec_ex(uint16_t address, uint8_t command, int repeat) {
    std::vector<uint32_t> sequences = {LEADING_PULSE, LONG_PAUSE};
    for (int i = 0; i < 16; i++) {
      sequences.push_back(PREFIX);
      sequences.push_back((address >> i) & 0x1? ONE_SUFFIX : ZERO_SUFFIX);
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

    add_repeat_code(sequences, repeat);
    send_nec_custom(sequences);
  }

}
