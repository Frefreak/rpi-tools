common = {
  'dependencies': [libgpio, libtimer],
  'install': true,
  'install_rpath': get_option('prefix') / 'lib',
}
executable('receiver', 'receiver.cc', kwargs: common)
executable('replay', 'replay.cc', kwargs: common)
executable('gpio_ctl', 'gpio_ctl.cc', kwargs: common)
executable('pulse_wave', 'pulse_wave.cc', kwargs: common)
