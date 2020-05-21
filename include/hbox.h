/*
 * hbox.h
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


#ifndef __LIBGUI_HBOX__
#define __LIBGUI_HBOX__

#include "widget.h"
#include <string>
#include "rect.h"
#include "video.h"
#include "renderer.h"
#include "event.h"
#include <map>
#include <iostream>

namespace LIBGUI {


class HBox : public Widget {
protected:
	std::map<std::string,Widget*>   _Child;
	std::map<std::string,Rect>      _ChildRect;
	int     _ChildCount;
	bool    _FixW;
	bool    _FixH;
	
public:		
	HBox ( Widget *parent, std::string ID );
	
	Renderer*   GetRenderer     ( void );
	Rect	    GetSize	        ( void );
	bool	    AddChild	    ( Widget *child, std::string ID );
	bool	    AddChild	    ( Widget *child, std::string ID, int width, int h ){}
	bool        ChangeChild     ( std::string ID );
	void	    ChangeSize	    ( Rect rect );
	void	    ProcessEvent	( Event *event );
	bool	    Draw	        (void );
	void        Update          ( void );
	void	    ChangeOffset    ( Point offset );
	Point	    GetOffset	    ( void );
	bool		IsFixedH		( void ){return _FixH;}
	bool		IsFixedW		( void ){return _FixW;}
	

	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
	
};


}//namespace LIBGUI

#endif //__LIBGUI_VBOX__
