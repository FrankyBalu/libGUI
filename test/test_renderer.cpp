#include "../include/renderer.h"
#include <iostream>
#include "../include/log.h"
#include "../include/event.h"


int main ()
{
	LIBGUI::RendererInfo info;
	LIBGUI::RawWindow *win;
	LIBGUI::Renderer *renderer;
	LOG->setPriority(LIBGUI::LOG_PRIORITY_VERBOSE);
	
	int index = LIBGUI::GetNumRenderDrivers ();
	
	std::cout << "Es gibt " << index << " Render driver" << std::endl;
	
	for (int i = 0; i<index; i++ )
	{
		LIBGUI::GetRenderDriverInfo ( i, &info );
		LIBGUI::PrintDriverInfo ( &info );
	}
	
	LIBGUI::lowVideo::Inst()->Init ( LIBGUI::lowVideo::Inst()->getVideoDriver(0).c_str());
	 win = LIBGUI::lowVideo::Inst()->CreateWindow ( "test", 100, 100, 400, 400, LIBGUI::WINDOW_SHOWN );

	 renderer = new LIBGUI::Renderer ( win );
	 renderer->SetDrawColor (255,255,255,0);
	 renderer->Clear();
	 renderer->SetDrawColor (0,255,0,0);
	 renderer->DrawPoint ( 50, 50 );
	 renderer->DrawLine ( 55, 55, 100, 100 );
	 LIBGUI::Rect rect(300, 300, 50, 50 );
	 renderer->DrawRect ( &rect );
	 LIBGUI::Rect rectfill(350, 350, 50, 50 );
	 renderer->DrawFillRect ( &rectfill );
	 renderer->Present();
	 bool run = true;
	 while ( run)
	 {
	 	LIBGUI::lowEvent::Inst()->Update();
	 	LIBGUI::Event ev = LIBGUI::lowEvent::Inst()->Get();
	 	//std::cout << "Event.type: " << ev.type << std::endl;
	 	if ( ev.Type == LIBGUI::QUIT)
	 		run = false;
	 		
	 }
	 
	// SDL_Delay (2000);
}
