/*
 * widget.h
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


#ifndef __LIBGUI_WIDGET__
#define __LIBGUI_WIDGET__

#include <string>
#include "rect.h"
#include "video.h"
#include "renderer.h"
#include "event.h"

namespace LIBGUI {


class Widget {
protected:
	std::string	_ID;
	Widget 		*_Parent;
	Renderer 	*_Renderer;
	Rect 		_Rect;
	Point 		_Offset;
	
	Widget(){}
	~Widget(){}
public:		
	virtual Renderer* 	GetRenderer 	( void ) = 0;
	virtual Rect		GetSize			( void ) = 0;
	virtual Point		GetOffset		( void ) = 0;
	
	virtual bool		AddChild		( Widget *child, std::string ID ) = 0;
	virtual bool		ChangeChild 	( std::string ID ) = 0;
	virtual void		ChangeSize		( Rect rect ) = 0;
	virtual void		ChangeOffset	( Point offset ) = 0;
	virtual void 		ProcessEvent	( Event *event ) = 0;
	virtual void		Update			( void ) = 0;
	virtual bool		Draw			( void ) = 0;
	virtual bool		IsFixedH		( void ) = 0;
	virtual bool		IsFixedW		( void ) = 0;
	

	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
};


}//namespace LIBGUI

#endif //__LIBGUI_WIDGET__
