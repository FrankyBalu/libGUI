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

#ifndef __CWIDGET__
#define __CWIDGET__

#include <string>
#include <SDL2/SDL.h>
#include "rect.h"
#include "event.h"

namespace LIBGUI {


class cWidget {
protected:
	cRect _rect;
	std::string _ID;
	cWidget *_parent;
	cWidget *_child;
    SDL_Renderer *_renderer;
    

public:
	virtual SDL_Renderer* 	getRenderer ( void ) = 0;
	virtual cRect 			getMySize 	( void ) = 0;
	virtual bool 			addChild 	( cWidget* child ) = 0;
    virtual void 			setSize 	( cRect size ) = 0;
	virtual void 			changeSize 	( cRect newSize ) = 0;
	virtual void 			update 		( sEvent event ) = 0;
	virtual void 			draw 		( void ) = 0;

    void 	(*onKlick) 		( void );
    void 	(*onPressed) 	( void );
    void 	(*onSlideH) 	( void );
    void 	(*onSlideV) 	( void );
    void 	(*onRelease)	( void );

};

}
#endif //__WIDGET__
