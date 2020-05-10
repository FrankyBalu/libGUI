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
