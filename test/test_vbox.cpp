/*
 * src.cpp
 * Copyright (C) 2020 Frank Kurbatsch <frank.kurbatsch@gmail.com>
 * 
 * Uhr is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Uhr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include <iostream>
#include "../include/button.h"
#include "../include/mainwindow.h"
#include "../include/vbox.h"
#include "../include/hbox.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace LIBGUI {

void klick ( void )
	{
		SPDLOG_INFO ("klick");
		std::cout << "klick "  << std::endl;
	}
	void press ( void )
	{
		SPDLOG_INFO ("pressed");
		std::cout << "pressed " << std::endl;
	}
	

class newButton : public LIBGUI::cButton
{
public:

		
	newButton (cWidget *parent, std::string str1, std::string str2 )
	: cButton ( parent, str1, str2 )
	{
		onKlick = &klick;
		onPressed = &press;
	}

};
}
 
int main ( int argc, char *argv[] )
{
	auto file_logger = spdlog::rotating_logger_mt("test_Button_Widget", "logs/test_VBox.log", 1048576 * 5, 5);
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%T] %l:\n   file: %@\n      func: [%!]:\n         %v%$");
    SPDLOG_INFO ("        libGUI\n    VBox test");
    LIBGUI::sEvent ev;
    LIBGUI::cMainWindow *win;
    win = new LIBGUI::cMainWindow ("Test_Window");
    win->open ();
    
    LIBGUI::cVBox *vbox;
    LIBGUI::cHBox *hbox1;
    LIBGUI::cHBox *hbox2;
    LIBGUI::cHBox *hbox3;
    vbox = new LIBGUI::cVBox( win );
    hbox1 = new LIBGUI::cHBox ( vbox );
    hbox2 = new LIBGUI::cHBox ( vbox );
    hbox3 = new LIBGUI::cHBox ( vbox );
    
    LIBGUI::newButton *button1;
    LIBGUI::newButton *button2;
    LIBGUI::newButton *button3;
    LIBGUI::newButton *button4;
    LIBGUI::newButton *button5;
    LIBGUI::newButton *button6;
    
    button1 = new LIBGUI::newButton (hbox1, "Test_Button", "button1" );
    button2 = new LIBGUI::newButton (hbox1, "Test_Button", "button2" );
    button3 = new LIBGUI::newButton (hbox2, "Test_Button", "button2" );
    button4 = new LIBGUI::newButton (hbox3, "Test_Button", "button2" );
    button5 = new LIBGUI::newButton (hbox3, "Test_Button", "button2" );
    button6 = new LIBGUI::newButton (hbox3, "Test_Button", "button2" );
    
    //button->load();
    while ( win->isOpen() )
    {
    	win->update (ev);
    	win->draw ();
    }
    return 0;
}
