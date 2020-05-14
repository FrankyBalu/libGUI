/*
 * point.cpp
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
 
#include "../include/point.h"

namespace LIBGUI {

Point::Point ( void )
:_x(0),_y(0)
{
}

Point::Point ( int x, int y )
:_x(x),_y(y)
{
}

Point::~Point ( void )
{
}

int Point::GetX ( void )
{
	return _x;
}

int Point::GetY ( void )
{
	return _y;
}

void Point::SetX ( int x )
{
	_x = x;
}

void Point::SetY ( int y )
{
	_y = y;
}

void Point::Set ( int x, int y )
{
	_x = x;
	_y = y;
}


Point& Point::operator= (const Point &rhs)
{
	_x = rhs._x;
	_y = rhs._y;  
	return *this;
}

bool Point::operator==( const Point& rhs)
{
	if ( _x == rhs._x && _y == rhs._y )
    	return true;
    else
    	return false;
}



} //namespace LIBGUI
