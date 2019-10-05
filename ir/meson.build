libir = shared_library('ir', ['nec.cc'], dependencies: [libgpio, libtimer], install: true)

libir = declare_dependency(link_with: libir,
  include_directories: '.',
  dependencies: [libgpio, libtimer])

executable('test_nec', 'test.cc', dependencies: [libir])
executable('test_nec_recv', 'test_recv.cc', dependencies: [libir])

executable('nec_re', ['ir_re.cc', 'nec_standard.cc'],
	   dependencies: [libir], install: true, install_rpath: get_option('prefix') / get_option('libdir'))
executable('nec_custom_re', ['ir_re.cc', 'nec_custom.cc'],
	   dependencies: [libir], install: true, install_rpath: get_option('prefix') / get_option('libdir'))
executable('tv_ctrl', ['tv_ctrl.cc'],
	   dependencies: [libir], install: true, install_rpath: get_option('prefix') / get_option('libdir'))

executable('ybof2_test', 'YBOF2_test.cc')

compiler = meson.get_compiler('cpp')
librf24 = compiler.find_library('rf24', required: false)
if librf24.found()
  executable('ac_ctrl', 'ac_ctrl.cc', cpp_pch: '../pch/CLI11.hh',
	     cpp_args: '-DUSE_RF24', dependencies: [librf24], install: true)
else
  executable('ac_ctrl', 'ac_ctrl.cc', cpp_pch: '../pch/CLI11.hh')
endif
