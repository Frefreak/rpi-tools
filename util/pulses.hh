#ifndef PULSES_H
#define PULSES_H

#include <stdint.h>
#include <vector>
#include <iostream>

typedef struct pulses {
  uint32_t pin;
  // microsecond
  uint32_t interval;
  uint64_t length;
  uint8_t *data;
} pulses_t;

void write_pulses(pulses_t &sample, char *fn)
{
  FILE *fp = fopen(fn, "wb");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  std::cout << "data length: " << sample.length << "\n";
  std::cout << "total length: " << 16 + sample.length << "\n";
  std::cout << "writing...\n";
  fwrite(&sample.pin, sizeof(sample.pin), 1, fp);
  fwrite(&sample.interval, sizeof(sample.interval), 1, fp);
  fwrite(&sample.length, sizeof(sample.length), 1, fp);
  fwrite(sample.data, sample.length, 1, fp);
  fclose(fp);
}

pulses_t read_pulses(char *fn)
{
  FILE *fp = fopen(fn, "rb");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  pulses_t result;
  fread(&result.pin, sizeof(result.pin), 1, fp);
  fread(&result.interval, sizeof(result.interval), 1, fp);
  fread(&result.length, sizeof(result.length), 1, fp);
  uint8_t *data = (uint8_t *)(malloc(result.length));
  if (data == NULL) {
    std::string info = std::string("malloc ") + std::to_string(result.length);
    perror(info.c_str());
    exit(EXIT_FAILURE);
  }
  fread(data, result.length, 1, fp);
  result.data = data;
  fclose(fp);
  return result;
}
#endif /* PULSES_H */
