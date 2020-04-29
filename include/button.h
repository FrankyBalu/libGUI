/*
 * button.h
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

#ifndef __BUTTON__
#define __BUTTON__

#include <string>
#include <SDL.h>
#include "widget.h"


namespace LIBGUI {

class cButton : public cWidget
{
private:

	/**
	 *	This is in future maybe a own class
	 */
	SDL_Texture *_theme; //shade/theme of the button
	SDL_Color _color1; //color of the button, not pressed
	SDL_Color _color2; //color of the button, if pressed

	std::string _label; //label of the button
	SDL_Texture *_labelTex; //Rendered Text
    SDL_Texture *_texture;

    bool load ( void );
public:

	                cButton ( cWidget *parent, std::string label = "std Button", std::string ID = "Button" );

    SDL_Renderer* getRenderer ( void );
	  cRect         getMySize   ( void );
	  bool          addChild    ( cWidget* child ){}
	  void          (*onKlick)  ( void );
    void          (*onPressed)( void );
    void          (*onSlideH) ( void );
    void          (*onSlideV) ( void );
    void          (*onRelease)( void );
    void          setSize     ( cRect size );
	  //Drawing
    void          draw        ( void );
	  void          update      ( sEvent event );

    
};
	
}

#endif //__PICTURE_WIDGET__
