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
	if ( (p.GetX() > _x && p.GetX() < (_x + _w )) &&
		 (p.GetY() > _y && p.GetY() < (_y + _h )))
		 return true;
	else
		return false;
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
