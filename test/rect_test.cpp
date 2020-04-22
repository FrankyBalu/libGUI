/*
 * rect_test.cpp
 * Copyright (C) 2020 Frank Kartheuser <frank.kurbatsch@gmail.com>
 * 
 * libGUI is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libGUI is distributed in the hope that it will be useful, but
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
#include "../include/rect.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
 
 
int main ( int argc, char *argv[] )
{
	auto file_logger = spdlog::rotating_logger_mt("rect_test", "logs/rect_test.log", 1048576 * 5, 5);
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("%^[%d.%m.%C %T]:[%l]: %@ %!:\n                             %v%$");
    SPDLOG_DEBUG ("libGUI rect_test");
	//Tests of point-class
	cPoint point1;
	cPoint point2( 30, 60 );
	cRect rect1;
	cRect rect2 ( 20, 20, 10, 100);
	cRect rect3 ( 50, 50);
	cRect rect4 (point1, 30, 30);
	
	point1.setPosX ( 10 );
	point1.setPosY ( 10 );
	point2.setPos  ( 40, 40 );
	rect1.setPosX ( 20 );
	rect1.setPosY ( 20 );
	rect2.setPos ( 80, 80 );
	rect3.setPos ( point2 );
	rect4.setHeight ( 100 );
	rect4.setWidth ( 100 );
	rect4.setSize ( 200, 200 );
		
	
	
	return 0;
	
}
