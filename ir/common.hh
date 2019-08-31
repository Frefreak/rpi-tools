#ifndef COMMON_H
#define COMMON_H

#include <cstdint>

typedef struct segment {
  uint32_t duration : 31;
  uint32_t level : 1;
} segment;

#endif /* COMMON_H */
