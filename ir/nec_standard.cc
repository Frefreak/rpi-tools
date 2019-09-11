#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>

std::string decode(std::vector<uint32_t> &seqs)
{
  std::vector<bool> buffer = {};
  for (int i = 2; i < 66; i += 2) {
    if (abs((int)seqs[i] - 560) < 100) {
      long m = round(seqs[i + 1] / (float)seqs[i]);
      if (m == 1) {
        buffer.push_back(false);
      } else if (m == 3) {
        buffer.push_back(true);
      } else {
      std::cout << "encountered duration tuple of " << seqs[i] << "," << seqs[i+1] << ", error out\n";
      }
    } else {
      std::cout << "encountered duration of " << seqs[i] << ", index " << i << ", error out\n";
      return "";
    }
  }
  uint32_t i = 68;
  int repeat = 0;
  while (seqs.size() >= i + 3) {
    if (abs((int)seqs[i] - 9000) < 400 &&
        abs((int)seqs[i+1] - 2250) < 200 &&
        abs((int)seqs[i+2] - 560) < 100) {
      repeat++;
    }
    i += 3;
  }

  assert(buffer.size() == 32);
  for (int i = 0; i < 8; i++) {
    if (buffer[i] == buffer[i+8]) {
      std::cout << "data doesn't looks like standand NEC protocol (address), error out";
      return "";
    }
  }
  for (int i = 16; i < 24; i++) {
    if (buffer[i] == buffer[i+8]) {
      std::cout << "data doesn't looks like standand NEC protocol (command), error out";
      return "";
    }
  }

  int addr = 0;
  for (int i = 7; i >= 0; i--) {
    addr = (addr << 1) | buffer[i];
  }
  int cmd = 0;
  for (int i = 23; i >= 16; i--) {
    cmd = (cmd << 1) | buffer[i];
  }
  char result[32];
  snprintf(result, 32, "addr: 0x%02x, cmd: 0x%02x, rep: %d", addr, cmd, repeat);

  return std::string(result);
}
