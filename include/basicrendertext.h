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
