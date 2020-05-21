/*
 * texture.h
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

#ifndef __LIBGUI_TEXTURE__
#define __LIBGUI_TEXTURE__

#include "../include/renderer.h"
#include <SDL2/SDL.h>
#include <map>
#include <iostream>
#include <string>

namespace LIBGUI {


class Texture{
private:
	std::map<std::string, SDL_Texture*> _Textures;  
	Renderer *_renderer;	
	Texture ( void );
	static Texture *_Instance;
	

public:
	static Texture *Inst();

	bool Init ( Renderer *renderer);
	bool Load ( std::string file, std::string ID );
	bool Load ( SDL_Surface *surface, std::string ID );
	bool Draw ( std::string ID, Rect *srcRect, Rect *destRect );
	Rect* Size ( std::string ID );
};

}//namespace LIBGUI

#endif //__LIBGUI_TEXTURE__
