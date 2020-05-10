project ('libGUI', ['cpp'],
	version: '0.0.1a',
    default_options : [
    'warning_level=3',
    'cpp_std=c++11',
    'buildtype=debug',
    'b_colorout=always',
    ],)
    
sdl2_dep = dependency('sdl2', method : 'pkg-config')
sdli_dep = dependency('SDL2_image', method : 'pkg-config')
sdlm_dep = dependency('SDL2_mixer', method : 'pkg-config')
sdlf_dep = dependency('SDL2_ttf', method : 'pkg-config')
sdl_dep = [ sdl2_dep, sdli_dep, sdlm_dep, sdlf_dep ]




sources = files(
  	'src/log.cpp',
  	'src/point.cpp',
  	'src/rect.cpp',
  	'src/video.cpp',
 	'src/renderer.cpp',
  	'src/event.cpp',
  	'src/window.cpp',
  	'src/texture.cpp',
  	'src/basicrendertext.cpp',
	'src/pushbutton.cpp',
	'src/vbox.cpp',
	'src/hbox.cpp',
	'src/topbar.cpp'
  )

incfiles = files( 
	'include/basicrendertext.h',
	'include/hbox.h',
	'include/point.h',
	'include/rect.h',
	'include/texture.h',
	'include/vbox.h',
	'include/widget.h',
	'include/event.h',
	'include/log.h',
	'include/pushbutton.h',
	'include/renderer.h',
	'include/topbar.h',
	'include/video.h',
	'include/window.h'
)

inc = include_directories('include')

libGUI = shared_library(
  'libGUI-0',
#  meson.project_name(),
  sources,
  version : '0.0.0',
  cpp_args : '-D_PRIVATELIBGUI -g',
  dependencies: [sdl_dep],
  install : true
)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libGUI,
                 version : '0.0.a', name : 'libGUI', filebase : 'libGUI', subdirs : 'libGUI' ,description : 
                 'A SDL2 based GUI-library')
install_headers(incfiles, subdir : 'libGUI')

