#include <sys/mman.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <iostream>
#include <string>

#include <gpio.hh>

namespace GPIO {
  GPIO::GPIO() {
    int fd = open("/dev/mem", O_RDWR);
    if (fd == -1) {
      perror("open /dev/mem");
      exit(errno);
    }
    reg = (uint8_t *)mmap(NULL, GPIO_REG_SIZE, PROT_READ | PROT_WRITE,
                                   MAP_SHARED, fd, GPIO_REG_BASE);
    if (reg == MAP_FAILED) {
      perror("mmap");
      exit(errno);
    }
    //std::cout << "mmap done: " << (void *)reg << '\n';
  }

  GPIO::~GPIO() {
    if (munmap((void *)reg, GPIO_REG_SIZE) == -1) {
      perror("munmap");
    }
  }
}
