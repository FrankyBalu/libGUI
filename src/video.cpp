/*
 * video.cpp
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

#include "../include/video.h"
#include "../include/log.h"
#include <SDL2/SDL.h>


namespace LIBGUI {

lowVideo *lowVideo::_Instance = 0;

lowVideo* lowVideo::Inst()
{
	if ( _Instance == 0 )
	{
		_Instance = new lowVideo();
	}
	return _Instance;
}


lowVideo::lowVideo ( void )
{
	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"lowVideo Objekt erstellt");
	_IsInit = false;
}


lowVideo::~lowVideo ( void )
{
	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"Lösche lowVideo Object");
	SDL_VideoQuit();
}

int lowVideo::getNumVideoDrivers ( void )
{
	return SDL_GetNumVideoDrivers ( );
}

std::string lowVideo::getVideoDriver ( int index )
{
	return SDL_GetVideoDriver ( index );
}

bool lowVideo::Init ( const char *driver_name )
{
	if (_IsInit)
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Videosystem wurde bereits Initialisiert");
		return false;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Initialisiere Videosubsystem mit Treiber %s...", driver_name);
	if ( SDL_VideoInit ( driver_name ) < 0 )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"...%s", SDL_GetError() );
		return false;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI,"...erfolgreich!");
	_IsInit = true;
	return true;	
}

RawWindow* lowVideo::CreateWindow ( std::string title, int x, int y, int w, int h, uint32_t flags )
{
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Erstelle Fenster: %s ...", title.c_str());
	SDL_Window* win = SDL_CreateWindow ( title.c_str(), x, y, w, h, flags );
	if ( win == nullptr )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"...%s", SDL_GetError());
		return nullptr;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI,"...erfolgreich");
	return (RawWindow*)win;
}

void lowVideo::DestroyWindow ( RawWindow *win )
{
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Zerstöre Fenster %s", SDL_GetWindowTitle((SDL_Window*) win));
	SDL_DestroyWindow ( (SDL_Window*)win );
}

void lowVideo::GetWindowSize(RawWindow *win, int *w, int *h)
{
	SDL_GetWindowSize((SDL_Window*)win, w, h);
}

}//namespace LIBGUI
