gpio_sources = ['gpio.cc']
libgpio = shared_library('gpio', gpio_sources, include_directories: '.', install: true)

libgpio = declare_dependency(link_with: libgpio, include_directories: '.')

executable('test_gpio', 'test.cc', dependencies: libgpio)
