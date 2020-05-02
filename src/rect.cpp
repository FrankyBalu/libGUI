/*
 * rect.cpp
 * Copyright (C) 2020 Frank Kurbatsch <frank.kurbatsch@gmail.com>
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

namespace LIBGUI {


cPoint::cPoint ( void )
{
	_x = 0;
	_y = 0;
}
 
cPoint::cPoint ( int x, int y )
{
	_x=x;
	_y=y;
}

cPoint::~cPoint ( void )
{

}

void cPoint::setPosX ( int x )
{
	_x = x;
}

void cPoint::setPosY ( int y )
{
	_y = y;
}

void cPoint::setPos ( int x, int y )
{
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
	_width = 1;
	_height = 1;
}

cRect::cRect ( int x, int y, int width, int height )
{
	_point.setPos ( x, y );
	_width = width;
	_height = height;	
}

cRect::cRect ( cPoint point, int width, int height )
{
	_point.setPos ( point.getPosX(), point.getPosY() );
	_width = width;
	_height = height;	
}


void cRect::setPosX ( int x )
{
	_point.setPosX ( x );
}

void cRect::setPosY ( int y )
{
	_point.setPosY ( y );
}

void cRect::setPos ( int x, int y )
{
	_point.setPos ( x, y );
}

void cRect::setPos ( cPoint point )
{
	_point.setPos ( point.getPosX(), point.getPosY() );
}

void cRect::setWidth ( int width )
{
	_width = width;
}

void cRect::setHeight ( int height )
{
	_height = height;
}

void cRect::setSize ( int width, int height )
{
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

}
