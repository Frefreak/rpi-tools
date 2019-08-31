#include "timer.hh"

namespace Timer {
  void Timer::set_duration(unsigned int usecs) {
    this->duration = new struct timespec();
    this->duration->tv_sec = 0;
    this->duration->tv_nsec = usecs * 1000;
  }

  void Timer::do_delay() {
    nanosleep(this->duration, NULL);
  }
}

