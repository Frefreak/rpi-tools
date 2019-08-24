#include <stdint.h>
#include <string>

// will use /dev/mem so this is the physical address
#define BCM2835_PERIPHERAL_BASE 0x20000000
#define BCM2836_PERIPHERAL_BASE 0x3f000000

#define GPIO_REG_OFFSET 0x200000

#define GPIO_REG_BASE (BCM2836_PERIPHERAL_BASE + GPIO_REG_OFFSET)

#define GPIO_REG_SIZE 0xb4

#define GPFSEL_OFFSET 0
#define GPSET_OFFSET 0x1c
#define GPCLR_OFFSET 0x28
#define GPLEV_OFFSET 0x34


namespace GPIO {

  // function selection
  enum func {
    input,
    output,
    // Alternative function value from documentation might be wrong
    // according to errata. Need to check in the future.
    alt_5,
    alt_4,
    alt_0,
    alt_1,
    alt_2,
    alt_3
  };

  using level = bool;

  struct GPIO {
    volatile uint8_t *reg;

    GPIO();
    ~GPIO();

    // level = 0 for low, other positive value for high
    inline void set_out(uint8_t pin, uint8_t level) {
      chk_pin(pin);
      uint8_t reg_offset = (level? GPSET_OFFSET: GPCLR_OFFSET) + pin / 32 * 4;
      uint32_t *out_reg = (uint32_t *)(reg + reg_offset);
      uint8_t shift = pin % 32;
      *out_reg |= 1 << shift;
    }

    inline level get(uint8_t pin) {
      chk_pin(pin);
      uint8_t reg_offset = GPLEV_OFFSET + pin / 32 * 4;
      uint32_t *set_reg = (uint32_t *)(reg + reg_offset);
      uint8_t shift = pin % 32;
      return (*set_reg >> shift) & 0b1;
    }

    inline func get_func(uint8_t pin) {
      chk_pin(pin);
      uint32_t* reg = func_sel_reg(pin);
      uint8_t shift = (pin % 10) * 3;
      uint8_t val = ((*reg) >> shift) & 0b111;
      return static_cast<func>(val);
    }

    inline void set_func(uint8_t pin, func mode) {
      chk_pin(pin);
      uint32_t *reg = func_sel_reg(pin);
      mode = static_cast<func>(mode & 0b111);
      uint8_t shift = (pin % 10) * 3;
      uint8_t val = ((*reg) >> shift) & 0b111;
      uint8_t mask = (val ^ mode) << shift;
      *reg ^= mask;
    }

    std::string get_func_str(uint8_t pin) {
      chk_pin(pin);
      switch (get_func(pin)) {
        case input:  return std::string("input");
        case output: return std::string("output");
        case alt_0:  return std::string("alternative_0");
        case alt_1:  return std::string("alternative_1");
        case alt_2:  return std::string("alternative_2");
        case alt_3:  return std::string("alternative_3");
        case alt_4:  return std::string("alternative_4");
        case alt_5:  return std::string("alternative_5");
        default:     return std::string("unknown function mode");
      }
    }

  private:
    void chk_pin(uint8_t pin) {
      if (pin < 0 || pin > 53)
        throw std::runtime_error("invalid pin number");
    }

    inline uint32_t *func_sel_reg(uint8_t pin) {
      chk_pin(pin);
      uint8_t reg_offset = GPFSEL_OFFSET + pin / 10 * 4;
      return (uint32_t *)(reg + reg_offset);
    }

  };
}
