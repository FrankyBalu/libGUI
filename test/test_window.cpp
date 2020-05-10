#include "../include/video.h"
#include "../include/window.h"
#include "../include/event.h"

bool isRunning = true;

int main ()
{
	LIBGUI::lowVideo::Inst()->Init ( LIBGUI::lowVideo::Inst()->getVideoDriver(0).c_str());
	
	LIBGUI::Window win ( "test window", 0, 0, 600, 600, LIBGUI::WINDOW_SHOWN | LIBGUI::WINDOW_RESIZABLE, "MainWindow" );
	win.GetRenderer()->SetDrawColor ( 255, 0, 0, 0 );
	
	while ( win.IsOpen() )
	{
		win.ProcessEvent();
		win.Update (  );
		win.Draw ();
	}
	return 0;
}
