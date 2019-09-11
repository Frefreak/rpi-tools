#ifndef NEC_H
#define NEC_H

#include <gpio.hh>
#include <timer.hh>
#include <vector>
#include <cstdint>
#include <stdio.h>
#include "common.hh"

namespace NEC {
  struct NEC {
    // no configuration for now
    NEC(uint32_t pin): pin(pin) {
      gpio = new GPIO::GPIO();
      gpio->set_func(pin, GPIO::output);
      timer = new Timer::Timer();
    };

    // send a standard nec packet
    void send_nec(uint8_t address, uint8_t command, int repeat=0);

    // send an extended nec packet (no inverse address)
    void send_nec_ex(uint16_t address, uint8_t command, int repeat=0);

    // send a packet with custom code (for somewhat complex devices),
    // starting with "one"
    void send_nec_custom(std::vector<uint32_t> &);

  private:
    uint32_t pin;
    GPIO::GPIO *gpio;
    Timer::Timer *timer;
    // all time constants are in microseconds
    // https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol
    uint32_t LEADING_PULSE = 9000; // 9 ms of leading agc pulse
    uint32_t LONG_PAUSE = 4500; // 4.5 ms of long pause in start
    uint32_t SHORT_PAUSE = 2250; // 2.25 ms of short pause in repeat code
    uint32_t REPEAT_DIST = 108000; // 108 ms between repeat code
    uint32_t PREFIX = 562; // 562.5 us of pulse leading '0' or '1', ignore 0.5 us here
    uint32_t ZERO_SUFFIX = PREFIX;
    uint32_t ONE_SUFFIX = 3 * PREFIX;
    uint32_t carrier_freq = 38222; // 38.222 KHZ carrier

    std::vector<segment> modulate(std::vector<uint32_t> &);
    void add_repeat_code(std::vector<uint32_t> &sequences, int repeat);
  };

  struct NEC_RECV {
    // no configuration for now
    NEC_RECV(uint32_t pin): pin(pin) {
      gpio = new GPIO::GPIO();
      gpio->set_func(pin, GPIO::input);
      timer = new Timer::Timer(); // use timer constructor to change scheduler
    };

    bool wait_for_leader(uint32_t duration);

    // try to sniff an code, expecting nec starting frame
    std::vector<uint32_t> recv_nec_custom(uint32_t duration);

  private:
    uint32_t pin;
    GPIO::GPIO *gpio;
    Timer::Timer *timer;
    GPIO::level active = 0;
  };
}

#endif
