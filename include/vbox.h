/*
 * vbox.h
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

#ifndef __LIBGUI_VBOX__
#define __LIBGUI_VBOX__

#include <string>
#include <SDL.h>
#include "widget.h"


namespace LIBGUI {

class cVBox : public cWidget
{
private:
    cWidget 	  *_childs[32];
    cRect   	  *_rects[32];
    int           _count;

public:

	              cVBox 		( cWidget *parent, std::string ID = "VBox" );

    SDL_Renderer* getRenderer 	( void );
	cRect         getMySize   	( void );
	bool          addChild    	( cWidget* child );
    void          changeSize  	( cRect newSize );
	void          (*onKlick)  	( void );
    void          (*onPressed)	( void );
    void          (*onSlideH) 	( void );
    void          (*onSlideV) 	( void );
    void          (*onRelease)	( void );
    void          setSize     	( cRect size );
	  //Drawing
    void          draw        	( void );
	void          update      	( sEvent event );
    
};
	
}//namespace LIBGUI

#endif //__LIBGUI_VBOX__
