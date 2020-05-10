#include "../include/log.h"
#include "../include/event.h"
#include <SDL.h>

namespace LIBGUI {

lowEvent *lowEvent::_Instance = 0;

lowEvent::lowEvent ( void )
{
}

lowEvent::~lowEvent ( void )
{
}

lowEvent* lowEvent::Inst ( void )
{
	if (_Instance == 0)
	{
		_Instance = new lowEvent();
    }
    return _Instance;
}


bool lowEvent::Update ( void )
{
	SDL_Event _SDLevent;
    if ( SDL_PollEvent( &_SDLevent ) > 0 )
    {
    	//Benutzer möchte das Program beenden
    	if ( _SDLevent.type == SDL_QUIT )
        {
        	_Event.Type = QUIT;
        	LOG->VERBOSE ("QUIT Event ausgelöst\n");
        	return true;
        }
        //Mausknopf wurde gedrückt
        if ( _SDLevent.type == SDL_MOUSEBUTTONDOWN )
        {
        	_Event.Type 		= MOUSEBUTTONDOWN;
        	_MouseButtonDown 	= true;
        	_Event.WindowID 	= _SDLevent.button.windowID;
        	_Event.NewW 		= 0;
        	_Event.NewH 		= 0;
        	_Event.X 			= _SDLevent.button.x;
        	_Event.Y 			= _SDLevent.button.y;
        	_Event.XRel 		= 0;
        	_Event.YRel 		= 0;
        	_Event.Clicks		= 0;
        	_Event.x 			= 0;
        	_Event.y			= 0;
        	_Event.xRel			= 0;
        	_Event.yRel			= 0;
        	LOG->VERBOSE ("MOUSEBUTTONDOWN: x: %d y: %d WindowID: %d\n", _Event.X, _Event.Y, _Event.WindowID);
        	return true;
		}
        if ( _SDLevent.type == SDL_MOUSEBUTTONUP )
        {
        	_Event.Type 		= MOUSEBUTTONUP;
        	_MouseButtonDown 	= false;
        	_Event.WindowID 	= _SDLevent.button.windowID;
        	_Event.NewW 		= 0;
        	_Event.NewH 		= 0;
        	_Event.X 			= _SDLevent.button.x;
        	_Event.Y 			= _SDLevent.button.y;
        	_Event.XRel 		= 0;
        	_Event.YRel 		= 0;
        	_Event.Clicks		= _SDLevent.button.clicks;
        	_Event.x 			= 0;
        	_Event.y			= 0;
        	_Event.xRel			= 0;
        	_Event.yRel			= 0;
        	LOG->VERBOSE ("MOUSEBUTTONUP: x: %d y: %d clicks: %d WindowID: %d\n", _Event.X, _Event.Y, _Event.Clicks, _Event.WindowID);
        	return true;
		}
        if ( _SDLevent.type == SDL_MOUSEMOTION && _MouseButtonDown )
        {
        	_Event.Type 		= MOUSEMOTION;
        	_Event.WindowID 	= _SDLevent.motion.windowID;
        	_Event.NewW 		= 0;
        	_Event.NewH 		= 0;
        	_Event.X 			= _SDLevent.motion.x;
        	_Event.Y 			= _SDLevent.motion.y;
        	_Event.XRel 		= _SDLevent.motion.xrel;
        	_Event.YRel 		= _SDLevent.motion.yrel;
        	_Event.Clicks		= 0;
        	_Event.x 			= 0;
        	_Event.y			= 0;
        	_Event.xRel			= 0;
        	_Event.yRel			= 0;
        	LOG->VERBOSE ("MOUSEMOTION: x: %d y: %d relx: %d rely: %d WindowID: %d\n", _Event.X, _Event.Y, _Event.XRel, _Event.YRel, _Event.WindowID);
        	return true;
		}
        
        if ( _SDLevent.type == SDL_FINGERDOWN )
        {
        	_Event.Type 		= FINGERDOWN;
        	_FingerDown		 	= true;
        	_Event.WindowID 	= _SDLevent.tfinger.windowID;
        	_Event.NewW 		= 0;
        	_Event.NewH 		= 0;
        	_Event.X 			= 0;
        	_Event.Y 			= 0;
        	_Event.XRel 		= 0;
        	_Event.YRel 		= 0;
        	_Event.Clicks		= 0;
        	_Event.x 			= _SDLevent.tfinger.x;
        	_Event.y			= _SDLevent.tfinger.y;
        	_Event.xRel			= 0;
        	_Event.yRel			= 0;
        	LOG->VERBOSE ("FINGERDOWN: x: %f y: %f  WindowID: %d\n", _Event.x, _Event.x, _Event.WindowID);
        	return true;
		}
        if ( _SDLevent.type == SDL_FINGERUP )
        {
        	_Event.Type 		= FINGERUP;
        	_FingerDown 		= false;
        	_Event.WindowID 	= _SDLevent.tfinger.windowID;
        	_Event.NewW 		= 0;
        	_Event.NewH 		= 0;
        	_Event.X 			= 0;
        	_Event.Y 			= 0;
        	_Event.XRel 		= 0;
        	_Event.YRel 		= 0;
        	_Event.Clicks		= 0;
        	_Event.x 			= _SDLevent.tfinger.x;
        	_Event.y			= _SDLevent.tfinger.y;
        	_Event.xRel			= 0;
        	_Event.yRel			= 0;
        	LOG->VERBOSE ("FINGERUP: x: %f y: %f  WindowID: %d\n", _Event.x, _Event.x, _Event.WindowID);
        	return true;
		}
        if ( _SDLevent.type == SDL_FINGERMOTION && _FingerDown)
        {
        	_Event.Type 		= FINGERMOTION;
        	_Event.WindowID 	= _SDLevent.tfinger.windowID;
        	_Event.NewW 		= 0;
        	_Event.NewH 		= 0;
        	_Event.X 			= 0;
        	_Event.Y 			= 0;
        	_Event.XRel 		= 0;
        	_Event.YRel 		= 0;
        	_Event.Clicks		= 0;
        	_Event.x 			= _SDLevent.tfinger.x;
        	_Event.y			= _SDLevent.tfinger.y;
        	_Event.xRel			= _SDLevent.tfinger.dx;
        	_Event.yRel			= _SDLevent.tfinger.dy;
        	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"FINGERMOTION: x: %f y: %f relx: %f rely: %f WindowID: %d\n", _Event.x, _Event.y, _Event.xRel, _Event.yRel, _Event.WindowID);
        	return true;
		}
		if ( (_SDLevent.type == SDL_WINDOWEVENT) && (_SDLevent.window.event == SDL_WINDOWEVENT_RESIZED) )
        {
        	_Event.Type 		= WINDOWRESIZE;
        	_Event.WindowID 	= _SDLevent.window.windowID;
        	_Event.NewW 		= _SDLevent.window.data1;
        	_Event.NewH 		= _SDLevent.window.data2;
        	_Event.X 			= 0;
        	_Event.Y 			= 0;
        	_Event.XRel 		= 0;
        	_Event.YRel 		= 0;
        	_Event.Clicks		= 0;
        	_Event.x 			= 0;
        	_Event.y			= 0;
        	_Event.xRel			= 0;
        	_Event.yRel			= 0;
        	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"WINDOWRESIZE: NewW: %d NewH: %d WindowID: %d\n", _Event.NewW, _Event.NewH, _Event.WindowID);
        	return true;
		}
	}
	LOG->VERBOSE (LOG_CATEGORY_LIBGUI,"Kein Benutzbares Event vorhanden\n");
	return false;
}

Event lowEvent::Get ( void )
{	
	//LOG->INFO (LOG_CATEGORY_LIBGUI,"GetEvent Type: %d Window: %d NewX: %d NewY: %d X: %d Y: %d\n", _Event.Type, _Event.WindowID, _Event.NewW, _Event.NewH, _Event.X, _Event.Y );
	//LOG->INFO (LOG_CATEGORY_LIBGUI,"         XRel: %d YRel: %d x: %f y: %f xRel: %f, yRel: %f", _Event.XRel, _Event.YRel, _Event.x, _Event.y, _Event.xRel, _Event.yRel);
	Event retEvent 	= _Event;
	_Event.Type		= NOEVENT;
	_Event.WindowID = 0;
	_Event.NewW		= 0;
	_Event.NewH		= 0;
	_Event.X		= 0;
	_Event.Y		= 0;
	_Event.XRel		= 0;
	_Event.YRel		= 0;
	_Event.x		= 0;
	_Event.y		= 0;
	_Event.xRel		= 0;
	_Event.yRel		= 0;
	if ( retEvent.Type > NOEVENT && retEvent.Type < LASTEVENT )
		return retEvent;
	else
		return _Event;
}
        
        
}//namespace LIBGUI
