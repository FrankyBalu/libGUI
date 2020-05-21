#include "../include/video.h"
#include "../include/window.h"
#include "../include/event.h"
#include "../include/pushbutton.h"
#include "../include/texture.h"
#include "../include/log.h"
#include "../include/vbox.h"
#include "../include/hbox.h"

#include <string>


void ChangeToMainWidget ( void *win )
{
	std::cout << "geht\n";
}

int main ()
{
  LOG->setPriority(LIBGUI::LOG_PRIORITY_ERROR);
	
	LIBGUI::lowVideo::Inst()->Init ( LIBGUI::lowVideo::Inst()->getVideoDriver(0).c_str());
	
	LIBGUI::Window win ( "test window", 0, 0, 1000, 700, LIBGUI::WINDOW_SHOWN | LIBGUI::WINDOW_RESIZABLE, "MainWindow" );
	
	LIBGUI::Texture::Inst()->Init ( win.GetRenderer());
	LIBGUI::basicRenderText::Inst()->Open ( "/opt/sample/font.ttf", 400 );
	
	LIBGUI::VBox vbox ( &win, "VBOX");
	LIBGUI::HBox hbox ( &vbox, "HBOX");
	LIBGUI::PushButton button( win.GetTopbar(), "Test" );
	button.onClick = ChangeToMainWidget;
	LIBGUI::PushButton button2 ( &vbox, "toogle");
	LIBGUI::PushButton button3 ( &hbox, "drei");
	LIBGUI::PushButton button4 ( &hbox, "vier");
	button.LabelPressed ( "Gedrückt", 255, 255, 255);
	button.LabelUnPressed ( "nicht Gedrückt", 255, 255, 255);
	button2.LabelPressed ( "Zwei", 255, 0, 0);
	button2.LabelUnPressed ( "Zwei", 0, 255, 0);
	button3.LabelPressed ( "Drei", 255, 0, 0);
	button3.LabelUnPressed ( "Drei", 0, 255, 0);
	button4.LabelPressed ( "Vier", 255, 0, 0);
	button4.LabelUnPressed ( "Vier", 0, 255, 0);
	button2.MakeCheckable (true);
	button4.MakeCheckable (true);
	win.GetRenderer()->SetDrawColor ( 0,255,0,0);
	while ( win.IsOpen() )
	{
		win.ProcessEvent();
		win.Update (  );
		win.Draw ();
	}
	return 0;
}
