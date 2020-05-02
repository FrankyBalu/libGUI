
test_rect_dep = ['../src/rect.cpp','test_rect.cpp']
test_window_dep = ['../src/rect.cpp','../src/mainwindow.cpp','test_window.cpp']
test_picture_dep = ['../src/rect.cpp','../src/mainwindow.cpp','../src/picture.cpp','test_picture.cpp']
test_button_dep = ['../src/rect.cpp','../src/mainwindow.cpp','../src/button.cpp','test_button.cpp']
test_hbox_dep = ['../src/rect.cpp','../src/mainwindow.cpp','../src/button.cpp','../src/hbox.cpp','test_hbox.cpp']
test_vbox_dep = ['../src/rect.cpp','../src/mainwindow.cpp','../src/button.cpp','../src/vbox.cpp','../src/hbox.cpp','test_vbox.cpp']

executable ('test_rect',  [test_rect_dep])
executable ('test_window', [test_window_dep],dependencies: [sdl_dep, sdli_dep])
executable ('test_picture', [test_picture_dep],dependencies: [sdl_dep, sdli_dep])
executable ('test_button', [test_button_dep],dependencies: [sdl_dep, sdli_dep])
executable ('test_hbox', [test_hbox_dep],dependencies: [sdl_dep, sdli_dep])
executable ('test_vbox', [test_vbox_dep],dependencies: [sdl_dep, sdli_dep])
