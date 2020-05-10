#include "../include/renderer.h"
#include "../include/log.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

namespace LIBGUI {

int GetNumRenderDrivers ( void )
{
	return SDL_GetNumRenderDrivers ( );
}

int GetRenderDriverInfo ( int index, RendererInfo *info )
{
	int ret = SDL_GetRenderDriverInfo ( index, (SDL_RendererInfo*)info );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Keine Information zu Treiber %d: %s", index, SDL_GetError() );
	}
	return ret;
}

void PrintDriverInfo ( RendererInfo *info )
{
	LOG->INFO (LOG_CATEGORY_LIBGUI,"\tRenderInfo:");
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Name: %s", info->name);
	LOG->INFO (LOG_CATEGORY_LIBGUI,"Flags: %d", info->flags);
	LOG->INFO (LOG_CATEGORY_LIBGUI,"max tex width: %d", info->max_texture_width);
	LOG->INFO (LOG_CATEGORY_LIBGUI,"max tex height: %d", info->max_texture_height);
}

Renderer::Renderer ( RawWindow *win )
{
	SDL_Renderer *ren = SDL_CreateRenderer ( (SDL_Window*)win, 0,  RENDERER_ACCELERATED | RENDERER_TARGETTEXTURE );
	if ( ren == nullptr )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Renderer nicht erzeugen: %s", SDL_GetError());
		_renderer = nullptr;
	}
	else
	{
		_renderer = (lowRenderer*)ren;
		_info = new RendererInfo;
		Info ();
		LOG->INFO ( LOG_CATEGORY_LIBGUI, "Renderer erfolgreich erstellt");
		PrintDriverInfo ( _info );
		_window = win;
	}
}

Renderer::Renderer ( RawWindow *win, int index, Uint32 flags )
{
	SDL_Renderer *ren = SDL_CreateRenderer ( (SDL_Window*)win, index,  flags );
	if ( ren == nullptr )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Renderer nicht erzeugen: %s", SDL_GetError());
		_renderer = nullptr;
	}
	else
	{
		_renderer = (lowRenderer*)ren;
		_info = new RendererInfo;
		Info ();
		LOG->INFO ( LOG_CATEGORY_LIBGUI, "Renderer erfolgreich erstellt");
		PrintDriverInfo ( _info );
		_renderer = (lowRenderer*)ren;
		_window = win;
	}
}

void Renderer::Info ( void )
{
	SDL_GetRendererInfo((SDL_Renderer*) _renderer,(SDL_RendererInfo*) _info);
}

Renderer::~Renderer ( void )
{
	SDL_DestroyRenderer ( (SDL_Renderer*)_renderer);
}

lowRenderer* Renderer::GetlowRenderer ( void )
{
	return (lowRenderer*)SDL_GetRenderer ( (SDL_Window*)_window);
}

int Renderer::SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int ret = SDL_SetRenderDrawColor ( (SDL_Renderer*)_renderer, r, g, b, a );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Renderfarbe nicht setzen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->INFO ( LOG_CATEGORY_LIBGUI, "Setze Renderfarbe:\n\tRot: %d\n\tGrün: %d\n\tBlau: %d\n\tAlpha: %d", r, g, b, a);
		return ret;
	}
}

int Renderer::GetDrawColor( Uint8 * r, Uint8 * g, Uint8 * b, Uint8 * a )
{
	int ret = SDL_GetRenderDrawColor ( (SDL_Renderer*)_renderer, r, g, b, a );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Renderfarbe nicht bekommen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->INFO ( LOG_CATEGORY_LIBGUI, "Renderfarbe:\n\tRot: %d\n\tGrün: %d\n\tBlau: %d\n\tAlpha: %d", *r, *g, *b, *a);
		return ret;
	}
}

int Renderer::Clear ( void )
{
	int ret = SDL_RenderClear ((SDL_Renderer*)_renderer);
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Renderausgabe nicht löschen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Renderausgabe gelöscht");
		return ret;
	}
}

void Renderer::Present( void )
{
	SDL_RenderPresent((SDL_Renderer*)_renderer);
}

int Renderer::DrawPoint( int x, int y)
{
	int ret = SDL_RenderDrawPoint((SDL_Renderer*)_renderer, x, y);
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Punkt nicht Zeichnen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Zeichne Punkt %dx%d", x, y);
		return ret;
	}
}

int Renderer::DrawPoint( Point &point )
{
	int ret = SDL_RenderDrawPoint((SDL_Renderer*)_renderer, point.GetX(), point.GetY());
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Punkt nicht Zeichnen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Zeichne Punkt %dx%d", point.GetX(), point.GetY());
		return ret;
	}
}

int Renderer::DrawLine( int x1, int y1, int x2, int y2)
{
	int ret = SDL_RenderDrawLine((SDL_Renderer*)_renderer, x1, y1, x2, y2 );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Line nicht Zeichnen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Zeichne Line %dx%d ---- %dx%d", x1, y1, x2, y2);
		return ret;
	}
}

int Renderer::DrawLine( Point &point1, Point &point2)
{
	int ret = SDL_RenderDrawLine((SDL_Renderer*)_renderer, point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY() );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Line nicht Zeichnen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Zeichne Line %dx%d ---- %dx%d", point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY());
		return ret;
	}
}

int Renderer::DrawRect( Rect *rect )
{
	SDL_Rect r;
	r.x = rect->GetX();
	r.y = rect->GetY();
	r.w = rect->GetW();
	r.h = rect->GetH();
	int ret = SDL_RenderDrawRect((SDL_Renderer*)_renderer, &r );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann Rect nicht Zeichnen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Zeichne Rect X: %d Y: %d W: %d H: %d", r.x, r.y, r.w, r.h);
		return ret;
	}
}

int Renderer::DrawFillRect( Rect * rect)
{
	SDL_Rect r;
	r.x = rect->GetX();
	r.y = rect->GetY();
	r.w = rect->GetW();
	r.h = rect->GetH();
	int ret = SDL_RenderFillRect((SDL_Renderer*)_renderer, &r );
	if ( ret != 0 )
	{
		LOG->ERROR ( LOG_CATEGORY_LIBGUI, "Kann gefülltes Rect nicht Zeichnen: %s", SDL_GetError());
		return ret;
	}
	else
	{
		LOG->VERBOSE ( LOG_CATEGORY_LIBGUI, "Zeichne gefülltes Rect X: %d Y: %d W: %d H: %d", r.x, r.y, r.w, r.h);
		return ret;
	}
}







}//namespace LIBGUI
