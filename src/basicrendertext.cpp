/*
 * basicrendertext.cpp
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
 
#include "../include/basicrendertext.h"
#include "../include/texture.h"
#include "../include/log.h"
#include <SDL_ttf.h>
#include <memory>
#include <chrono>

namespace LIBGUI {

basicRenderText *basicRenderText::_Instance = 0;

basicRenderText::basicRenderText ( void )
{
	TTF_Init ();
}

basicRenderText* basicRenderText::Inst( void )
{
	if ( _Instance == 0 )
		_Instance = new basicRenderText();
	return _Instance;
}

bool basicRenderText::Open ( std::string file, int size )
{
	_font = TTF_OpenFont ( file.c_str(), size );
	if ( _font == nullptr )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Konnte Font(%s) nicht laden: %s",file.c_str(), SDL_GetError());
		return false;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Font(%s) erfolgreich laden",file.c_str());
	return true;
}

lowRenderText* basicRenderText::Render ( std::string text, uint8_t r, uint8_t g, uint8_t b )
{
	SDL_Surface *sur = TTF_RenderUTF8_Blended ( (TTF_Font*)_font, text.c_str(), SDL_Color {r,g,b,255} );
	if ( sur == nullptr )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI, "Konnte Text(%s) Surface nicht erstellen: %s", text.c_str(), SDL_GetError());
		return nullptr;
	}
		
	std::string ID = text + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
	if (!Texture::Inst()->Load ( sur, ID ))
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI, "Konnte Text(%s) nicht erstellen: %s", text.c_str(), SDL_GetError());
		//return nullptr;
	}
	lowRenderText *ret;
	ret = new lowRenderText;
		
	ret->Size.SetSize ( sur->w, sur->h );
	ret->ID = ID;
	LOG->INFO (LOG_CATEGORY_LIBGUI,"RenderText (ID: %s W: %d H: %d) erfolgreich erstellt", ID.c_str(), sur->w, sur->h);
	return ret;
}

}//namespace LIBGUI



