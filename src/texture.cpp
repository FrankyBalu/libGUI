#include "../include/texture.h"
#include "../include/log.h"
#include <SDL2/SDL_image.h>
#include <utility> 
#include <memory>

namespace LIBGUI {

Texture *Texture::_Instance = 0;


Texture* Texture::Inst ()
{
	if ( _Instance == 0 )
	{
		_Instance = new Texture();
	}
	return _Instance;
}

Texture::Texture ( void )
{
}

bool Texture::Init ( Renderer *renderer)
{
	if ( IMG_Init ( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP ) == 0 )
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Konnte SDL_Image nicht initialisieren: %s", SDL_GetError());
		return false;
	}
	_renderer = renderer;
	return true;
}
	
bool Texture::Load ( std::string file, std::string ID )
{
	if ( _Textures.count (ID) > 0)
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Texture mit der selben ID(%s) existiert schon", ID.c_str());
		return false;
	}
	SDL_Texture *tex = IMG_LoadTexture ( (SDL_Renderer*)_renderer->GetlowRenderer(), file.c_str() );
	if ( tex == nullptr )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Konnte Texture (%s/%s) nicht laden: %s",file.c_str(), ID.c_str(), SDL_GetError());
		return false;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Texture File: %s ID: %s erfolgreich geladen", file.c_str(), ID.c_str());
	_Textures[ID] = tex;
	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"Texture beinhaltet %ld Texturen", _Textures.size());
	return true;
}

bool Texture::Load ( SDL_Surface *surface, std::string ID )
{
	if ( _Textures.count (ID) > 0)
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Texture mit der selben ID(%s) existiert schon", ID.c_str());
		return false;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface((SDL_Renderer*)_renderer->GetlowRenderer(), surface);
	if ( tex == nullptr )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Konnte Texture (SDL_Surface/%s) nicht laden: %s", ID.c_str(), SDL_GetError());
		return false;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Texture von SDL_Surface ID: %s erfolgreich geladen", ID.c_str());
	_Textures[ID] = tex;
	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"Texture beinhaltet %ld Texturen", _Textures.size());
	return true;
}
	
Rect* Texture::Size ( std::string ID )
{
	if ( _Textures.count (ID) > 0)
	{
		int w, h;
		unsigned int format;
		int access;
		SDL_QueryTexture(_Textures[ID], &format, &access, &w, &h);
		std::shared_ptr<Rect> r(new Rect);
		r->SetSize ( w, h );
		LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"Texture W: %d H: %d", w, h);
		return r.get();
	}
	else
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Texture %s existiert nicht", ID.c_str() );
		std::shared_ptr<Rect> r(new Rect);
		return r.get();
	}
}
bool Texture::Draw ( std::string ID, Rect *srcRect, Rect *destRect )
{
	SDL_Rect src, dest;
	src.x = srcRect->GetX();
	src.y = srcRect->GetY();
	src.h = srcRect->GetH();
	src.w = srcRect->GetW();
	dest.x = destRect->GetX();
	dest.y = destRect->GetY();
	dest.h = destRect->GetH();
	dest.w = destRect->GetW();
	#ifdef LOG_DRAWING
	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"Texture draw %", ID);
	#endif
	SDL_RenderCopy ( (SDL_Renderer*)_renderer->GetlowRenderer(), _Textures[ID], &src, &dest );
	return true;
}


}
