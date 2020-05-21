#include "../include/video.h"
#include "../include/log.h"
#include <iostream>
#include <SDL2/SDL.h>

int main ()
{
	LOG->setPriority(LIBGUI::LOG_PRIORITY_VERBOSE);
	LIBGUI::RawWindow *win;
	
	int dr = LIBGUI::lowVideo::Inst()->getNumVideoDrivers();
	LOG->INFO ("Videotreiber:");
		
	for ( int i = 0; i < dr; i++ )
	{
		LOG->INFO ("Videotreiber %d: %s",i, LIBGUI::lowVideo::Inst()->getVideoDriver(i).c_str());
	}
	LIBGUI::lowVideo::Inst()->Init ( LIBGUI::lowVideo::Inst()->getVideoDriver(0).c_str());
	 
	 win = LIBGUI::lowVideo::Inst()->CreateWindow ( "test", 100, 100, 300, 300, LIBGUI::WINDOW_SHOWN );
	 
	 if ( win != nullptr )
	 	SDL_Delay (2000);
	return 0;
}
