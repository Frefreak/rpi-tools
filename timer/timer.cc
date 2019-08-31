#include "timer.hh"

namespace Timer {
  Timer::Timer() {
#ifdef __linux
    struct sched_param param = {};
    // should be fine?
    param.sched_priority = 10;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
      perror("sched_setscheduler");
      fprintf(stderr, "timer functionality will be inaccurate!");
    }
#elif __APPLE__
    fprintf(stderr, "this is not meant to be used in mac, just make it compiles");
#endif

  }

  void Timer::set_duration(unsigned int usecs) {
    this->duration = new struct timespec();
    this->duration->tv_sec = 0;
    this->duration->tv_nsec = usecs * 1000;
  }

  void Timer::do_delay() {
    nanosleep(this->duration, NULL);
  }
}

