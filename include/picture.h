/*
 * picture.h
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

#ifndef __LIBGUI_PICTURE__
#define __LIBGUI_PICTURE__

#include <SDL2/SDL.h>
#include "widget.h"
#include "mainwindow.h"
#include "event.h"
#include <string>

namespace LIBGUI {


class cPicture : public cWidget {
private:
	std::string   	_filePath;
	SDL_Texture*  	_texture;

public:
					cPicture    	( cWidget* parent, std::string file, std::string id = "PictureWidget" );
	SDL_Renderer* 	getRenderer 	( void );
	cRect         	getMySize   	( void );
	void          	draw        	( void );
	bool          	addChild    	( cWidget* child ){return false;}
	void 			changeSize 		( cRect newSize );
    void          	update      	( sEvent event );
    void          	(*onKlick)  	( void );
    void          	(*onPressed)	( void );
    void          	(*onSlideH) 	( void );
    void          	(*onSlideV) 	( void );
    void          	setSize 		(cRect rect) {}
	bool          	load        	( void );

};


}//namespace LIBGUI

#endif //__LIBGUI_PICTURE__
