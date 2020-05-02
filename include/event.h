/*
 * event.h
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

#ifndef __LIBGUI_EVENT__
#define __LIBGUI_EVENT__


#include <SDL2/SDL.h>

namespace LIBGUI {


typedef enum EVENTTYPE { NOEVENT, KLICKED, HOLD, SLIDEHORIZONTAL, SLIDEVERTICAL, QUIT } EVENTTYPE;


typedef struct sEvent {
	EVENTTYPE type;
  	int x;
  	int y;
  	int relX;
  	int relY;
  	bool down;
} sEvent;


} //namespace LIBGUI

#endif //__LIBGUI_EVENT__  
