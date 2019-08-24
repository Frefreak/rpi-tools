#ifndef PULSES_H
#define PULSES_H

#include <stdint.h>
#include <vector>

typedef struct pulses {
  uint8_t pin;
  // probably precise enough
  float interval;
  uint64_t length;
  uint8_t *data;
} pulses;


#endif /* PULSES_H */
