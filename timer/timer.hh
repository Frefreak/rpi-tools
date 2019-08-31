#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <sched.h>
#include <stdio.h>

namespace Timer {
  struct Timer {
    Timer();
    // the passed in value should be small enough
    void set_duration(unsigned int usecs);
    void do_delay();
  private:
    struct timeval *duration = nullptr;
    struct timeval start;
    struct timeval end;
  };
}

#endif /* TIMER_H */
