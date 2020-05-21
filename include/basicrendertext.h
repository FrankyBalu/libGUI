/*
 * basicrendertext.h
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

#ifndef __LIBGUI_BASICRENDERTEXT__
#define __LIBGUI_BASICRENDERTEXT__

#include <string>
#include "rect.h"

namespace LIBGUI {


typedef struct lowRenderText {
	std::string ID;
	Rect Size;
} lowRenderText;


class basicRenderText {
private:
	void *_font;
	static basicRenderText *_Instance;
	basicRenderText ( void );
	
public:

	static basicRenderText* Inst ( void );
	
	
	bool Open ( std::string file, int size );
	
	/*
	 *	rendert den angegebenen text in eine Textur,
	 * die farbe des textes wir in grb angegeben
	 * gibt den renderText zurück
	 */
	lowRenderText* Render ( std::string text, uint8_t r, uint8_t g, uint8_t b );



};




}//namespace LIBGUI

#endif //__LIBGUI_BASICRENDERTEXT__
