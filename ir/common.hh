#ifndef COMMON_H
#define COMMON_H

#include <cstdint>

typedef struct segment {
  uint32_t duration : 31;
  uint32_t level : 1;
} segment;

segment mk_seg(uint32_t duration, uint32_t level)
{
  return segment{duration, level > 0? 1u: 0u};
}

#endif /* COMMON_H */
