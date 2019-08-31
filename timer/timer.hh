#ifndef TIMER_H
#define TIMER_H

#include <time.h>

namespace Timer {
  struct Timer {
    // the passed in value should be small enough
    void set_duration(unsigned int usecs);
    void do_delay();
  private:
    struct timespec *duration = nullptr;
  };
}

#endif /* TIMER_H */
