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
