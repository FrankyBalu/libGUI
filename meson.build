project ('libGUI', ['cpp'],
	version: '0.0.1a',
    default_options : [
    'warning_level=1',
    'cpp_std=c++11',
    'buildtype=debug',
    'b_colorout=always',
    ],)
    
sdl_dep = dependency('sdl2', method : 'pkg-config')
sdli_dep = dependency('SDL2_image', method : 'pkg-config')
subdir ('test')
