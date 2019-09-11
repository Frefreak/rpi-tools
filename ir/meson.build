libir = shared_library('ir', ['nec.cc'], dependencies: [libgpio, libtimer], install: true)

libir = declare_dependency(link_with: libir,
  include_directories: '.',
  dependencies: [libgpio, libtimer])

executable('test_nec', 'test.cc', dependencies: [libir])
executable('test_nec_recv', 'test_recv.cc', dependencies: [libir])

executable('nec_re', ['ir_re.cc', 'nec_standard.cc'],
	   dependencies: [libir], install: true)
