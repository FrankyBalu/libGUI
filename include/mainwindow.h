/*
 * mainwindow.h
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

#ifndef __LIBGUI_MAINWINDOW__
#define __LIBGUI_MAINWINDOW__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "rect.h"
#include "widget.h"
#include "event.h"

namespace LIBGUI {

typedef enum _SLIDETYPE { NONE, VERTICALSLIDE, HORIZONTALSLIDE } _SLIDETYPE;


class cMainWindow : public cWidget {
protected:
	SDL_Window    	*_window;
	int				_flags;
	bool			_isOpen;

private:
    SDL_Event     	_event;
    sEvent        	_sEvent;
    _SLIDETYPE    	_sType;
    bool          	_hold;
    bool          	_buttonDown;
    Uint32        	_startTime;
    Uint32        	_klickTime;
    Uint32        	_holdTime;
    int           	_xStart;
    int           	_xRel;
    int           	_xNow;
    int           	_yStart;
    int           	_yRel;
    int           	_yNow;

    void          	_updateEvent	( void );
    void          	_init 			( int posX, int posY, int width, int height, int flags, std::string ID );

public:

	                cMainWindow 	( std::string ID = "Mainwindow" );
	                cMainWindow 	( int posX, int posY, int width, int height, int flags, std::string ID = "Mainwindow" );

	SDL_Renderer* 	getRenderer 	( void );
	cRect         	getMySize   	( void );
	bool          	addChild    	( cWidget* child );
    void          	setSize     	( cRect size );
    void 			changeSize 		( cRect rect ){}


	void          	(*onKlick)  	( void );
    void          	(*onPressed)	( void );
    void          	(*onSlideH) 	( void );
    void          	(*onSlideV) 	( void );
    void          	(*onRelease)	( void );

	  //Drawing
	void			draw        	( void );


	bool          	open        	( void );
	void          	update      	( sEvent event );
	bool          	isOpen      	( void );

    void          	setKlickTime	( Uint32 time );
    void          	setHoldTime 	( Uint32 time );

};


}//namespace LIBGUI

#endif //__LIBGUI_MAINWINDOW__
