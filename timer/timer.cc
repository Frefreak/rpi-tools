#include "timer.hh"

namespace Timer {
  Timer::Timer() {
#ifdef __linux
    struct sched_param param = {};
    // should be fine?
    param.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
      perror("sched_setscheduler");
      fprintf(stderr, "timer functionality will be inaccurate!\n");
    }
#elif __APPLE__
    fprintf(stderr, "this is not meant to be used in mac, just make it compiles");
#endif

  }

  void Timer::set_duration(unsigned int usecs) {
    this->duration = new struct timeval();
    this->duration->tv_sec = 0;
    this->duration->tv_usec = usecs;
  }

  void Timer::do_delay() {
    gettimeofday(&this->start, NULL);
    timeradd(&this->start, this->duration, &this->end);
    while (timercmp(&this->start, &this->end, <)) {
      gettimeofday (&this->start, NULL);
    }
  }
}

