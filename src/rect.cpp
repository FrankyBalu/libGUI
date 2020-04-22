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
#include "../include/rect.h"
#include <spdlog/spdlog.h>
//#include <spdlog/sinks/basic_file_sink.h>
 
cPoint::cPoint ( void )
{
	SPDLOG_DEBUG ("Create point X:0 Y:0");
	_x = 0;
	_y = 0;
}
 
cPoint::cPoint ( int x, int y )
{
	SPDLOG_DEBUG ("create point X:{} Y:{}", x, y);
	_x=x;
	_y=y;
}

cPoint::~cPoint ( void )
{

}

void cPoint::setPosX ( int x )
{
	SPDLOG_DEBUG ("Change X({}) to {}", _x, x);
	_x = x;
}

void cPoint::setPosY ( int y )
{
	SPDLOG_DEBUG ("Chaneg Y({}) to {}", _y, y);
	_y = y;
}

void cPoint::setPos ( int x, int y )
{
	char msg[128];
	sprintf (msg, "Change X(%d) to %d and Y(%d) to %d", _x, x, _y, y);
	SPDLOG_DEBUG ("Change X({}) to {} and Y({}) to {}", _x, x, _y, y);
	_x = x;
	_y = y;
}

int cPoint::getPosX ( void )
{
	return _x;
}

int cPoint::getPosY ( void )
{
	return _y;
}



cRect::cRect ( void )
{
	SPDLOG_DEBUG ("Create rect: X=0 Y=0 width=1 height=1");
	_width = 1;
	_height = 1;
}

cRect::cRect ( int x, int y, int width, int height )
{
	SPDLOG_DEBUG ("Create rect: X={} Y={} width={} height={}", _point.getPosX(), _point.getPosY(), _width, _height);
	_point.setPos ( x, y );
	_width = width;
	_height = height;	
}

cRect::cRect ( cPoint point, int width, int height )
{
	SPDLOG_DEBUG ("Create rect: X={} Y={} width={} height={}", _point.getPosX(), point.getPosY(), _width, _height);
	_point.setPos ( point.getPosX(), point.getPosY() );
	_width = width;
	_height = height;	
}


void cRect::setPosX ( int x )
{
	SPDLOG_DEBUG ("Change X({}) to {}", _point.getPosX(), x);
	_point.setPosX ( x );
}

void cRect::setPosY ( int y )
{
	SPDLOG_DEBUG ("Change Y({}) to {}", _point.getPosY(), y);
	_point.setPosY ( y );
}

void cRect::setPos ( int x, int y )
{
	SPDLOG_DEBUG ("Change X({}) to {} and Y({}) to {}", _point.getPosX(), x, _point.getPosY(), y);
	_point.setPos ( x, y );
}

void cRect::setPos ( cPoint point )
{
	SPDLOG_DEBUG ("Change X({}) to {} and Y({}) to {}", _point.getPosX(), point.getPosX(), _point.getPosY(), point.getPosY());
	_point.setPos ( point.getPosX(), point.getPosY() );
}

void cRect::setWidth ( int width )
{
	SPDLOG_DEBUG ("Change width({}) to {}", _width, width);
	_width = width;
}

void cRect::setHeight ( int height )
{
	SPDLOG_DEBUG ("Change height({}) to {}", _height, height);
	_height = height;
}

void cRect::setSize ( int width, int height )
{
	SPDLOG_DEBUG ("Change width({}) to {} and height({}) to {}", _width, width, _height, height);
	_width = width;
	_height = height;
}

cPoint cRect::getPos ( void )
{
	return _point;
}

int cRect::getPosX ( void )
{
	return _point.getPosX();
}

int cRect::getPosY ( void )
{
	return _point.getPosY();
}

int cRect::getHeight ( void )
{
	return _height;
}

int cRect::getWidth ( void )
{
	return _width;
}
