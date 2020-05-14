/*
 * point.h
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


#ifndef __LIBGUI_POINT__
#define __LIBGUI_POINT__


namespace LIBGUI {


class Point {
protected:
	int _x, _y;

public:
	Point ( void );
	Point ( int x, int y );
	
	~Point ( void );
	
	int GetX ( void );
	int GetY ( void );
	
	void SetX ( int x );
	void SetY ( int y );
	void Set ( int x, int y );
	
	
	
	Point &operator= ( const Point &rhs);
	bool operator==(const Point& rhs);

};


}//namespace LIBGUI

#endif //__LIBGUI_POINT__
