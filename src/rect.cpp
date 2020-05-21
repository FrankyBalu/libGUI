/*
 * rect.cpp
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
 
#include "../include/rect.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace LIBGUI {

Rect::Rect ( void )
:Point ( )
{
	_w = 0;
	_h = 0;
}

Rect::Rect ( Point p, int w, int h )
{
	_x = p.GetX();
	_y = p.GetY();
	_w = w;
	_h = h;
}

Rect::Rect ( int x, int y, int w, int h )
: Point ( x, y )
{
	_w = w;
	_h = h;
}

Rect::~Rect()
{

}


int Rect::GetW ( void )
{
	return _w;
}

int Rect::GetH ( void )
{
	return _h;
}


void Rect::SetW ( int w )
{
	_w = w;
}

void Rect::SetH ( int h )
{
	_h = h;
}


void Rect::SetSize ( int w, int h )
{
	_w = w;
	_h = h;
}

	
bool Rect::PointIsIn ( Point p )
{
	//std::cout << "\t\tPointIsIn Point: " << p.GetX() << "x" << p.GetY() <<std::endl;
	//std::cout << "\t\t          Rect : " << _x << "x" << _y << "  " << _w << "x" << _h << std::endl;
	if ( (p.GetX() > _x && p.GetX() < (_x + _w )) &&
		 (p.GetY() > _y && p.GetY() < (_y + _h )))
	{
		//std::cout <<"\t\tstimmt\n";
		 return true;
	}
	else
	{
		//std::cout <<"\t\tstimmt nicht\n";
		return false;
	}
}

bool Rect::HasIntersection ( Rect& r )
{
	SDL_Rect a,b;
	a.x = _x;
	a.y = _y;
	a.h = _h;
	a.w = _w;
	a.x = r.GetX();
	a.y = r.GetY();
	a.h = r.GetH();
	a.w = r.GetW();
	
	return SDL_HasIntersection ( &a, &b );
}
	
/*const Rect &Rect::operator= ( const Point &rhs)
{
	int x = rhs.GetX();
	int y = rhs.GetY();
	this->_x = x;
	this->_y = y;
	return *this;
}*/

Rect &Rect::operator= ( const Rect &rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	_w = rhs._w;
	_h = rhs._h;
	return *this;
}

bool Rect::operator==(const Rect& rhs)
{
	if ( ( _x == rhs._x) &&
			( _y == rhs._y ) &&
		 ( _w == rhs._w ) &&
		 ( _h == rhs._h ))
		 return true;
	else
		return false; 
}

	
} //namespace LIBGUI
