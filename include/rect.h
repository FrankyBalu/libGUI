/*
 * rect.h
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


#ifndef __LIBGUI_RECT__
#define __LIBGUI_RECT__

#include "point.h"
#include <SDL2/SDL.h>

namespace LIBGUI {

class Rect : public Point {
protected:
	int _w, _h;
	
public:
	Rect ( void );
	Rect ( Point p, int w, int h );
	Rect ( int x, int y, int w, int h );
	
	~Rect();
	
	
	int GetW ( void );
	int GetH ( void );
	
	void SetW ( int w );
	void SetH ( int h );
	void SetSize ( int w, int h );
	
	
	/**
	 * \brief Überprüft ob sich der angegebene Punkt im Rect befindet
	 */
	bool PointIsIn ( Point p );
	
	/**
	 * \brief Überprüft ob dieses Rect und das das als paramerer angegebene Rect
	 *			überschneiden
	 *
	 * \return true wenn es einen Schnittpunkt gibt, sonst false
	 */
	bool HasIntersection ( Rect& r );
	
	//Rect &operator= ( const Point &rhs);
	Rect &operator= ( const Rect &rhs);
	bool operator==(const Rect& rhs);

};

} //namespace LIBGUI

#endif //__LIBGUI_RECT__
