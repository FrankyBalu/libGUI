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
#include "../include/mainwindow.h"
#include "../include/event.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>


int main ( int argc, char *argv[] )
{
	auto file_logger = spdlog::rotating_logger_mt("window_test", "logs/test_window.log", 1048576 * 5, 5);
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("%l:\n[%d.%m.%C %T] file: %@ func: [%!]:\n                             %v");
    SPDLOG_INFO ("    libGUI\n    window_test");

	LIBGUI::sEvent ev;
	LIBGUI::cMainWindow win;

    win.open ();

    while ( win.isOpen() )
    {
    	win.update ( ev );
    }
    return 0;
}
