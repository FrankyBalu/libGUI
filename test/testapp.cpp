#include "../include/video.h"
#include "../include/window.h"
#include "../include/event.h"
#include "../include/pushbutton.h"
#include "../include/texture.h"
#include "../include/log.h"
#include "../include/vbox.h"
#include "../include/hbox.h"
#include <string>

/**
 *	Widget namen für topbar*/
#define SYSTEMWIDGET "SystemWidget"
#define TERRARIUMWIDGET "TerrariumWidget"
#define MUSICWIDEGT "MusicWidegt"
#define INFOWIDGET	"InfoWidget"

void ChangeToSystemWidget ( void *data )
{
	static_cast<LIBGUI::Window*>(data)->ChangeChild (SYSTEMWIDGET);
}

void ChangeToTerrariumWidget ( void *win )
{
	static_cast<LIBGUI::Window*>(win)->ChangeChild (TERRARIUMWIDGET);
}

void ChangeToMusicWidegt ( void *win )
{
	static_cast<LIBGUI::Window*>(win)->ChangeChild (MUSICWIDEGT);
}

void ChangeToInfoWidget ( void *win )
{
	static_cast<LIBGUI::Window*>(win)->ChangeChild (INFOWIDGET);
}





int main ()
{
	LOG->setPriority(LIBGUI::LOG_PRIORITY_INFO);	
	LIBGUI::lowVideo::Inst()->Init ( LIBGUI::lowVideo::Inst()->getVideoDriver(0).c_str());	
	LIBGUI::Window *MainWindow = new LIBGUI::Window ( "Test Program", 0, 0, 800, 480, LIBGUI::WINDOW_SHOWN | LIBGUI::WINDOW_RESIZABLE, "MainWindow" );
	LIBGUI::Texture::Inst()->Init ( MainWindow->GetRenderer());
	LIBGUI::basicRenderText::Inst()->Open ( "/opt/sample/font.ttf", 40 );
	//Topbar widgets
	LIBGUI::PushButton *MusicButton = new LIBGUI::PushButton( MainWindow->GetTopbar(), "cMusicButton" );
	MusicButton->onClick = &ChangeToMusicWidegt;
	MusicButton->LabelPressed ( "Musik", 255, 255, 255);
	MusicButton->LabelUnPressed ( "Musik", 255, 255, 255);
	LIBGUI::PushButton *SystemButton = new LIBGUI::PushButton( MainWindow->GetTopbar(), "aSystemButton" );
	SystemButton->onClick = &ChangeToSystemWidget;
	SystemButton->LabelPressed ( "Info", 0, 255, 0);
	SystemButton->LabelUnPressed ( "Info", 0, 0, 0);
	LIBGUI::PushButton *TerrariumButton = new LIBGUI::PushButton( MainWindow->GetTopbar(), "bTerrariumButton" );
	TerrariumButton->onClick = &ChangeToTerrariumWidget;
	TerrariumButton->LabelPressed ( "Terrarium", 255, 255, 255);
	TerrariumButton->LabelUnPressed ( "Terrarium", 255, 255, 255);
	LIBGUI::PushButton *InfoButton = new LIBGUI::PushButton( MainWindow->GetTopbar(), "dInfoButton" );
	InfoButton->onClick = &ChangeToInfoWidget;
	InfoButton->LabelPressed ( "System", 255, 255, 255);
	InfoButton->LabelUnPressed ( "System", 255, 255, 255);
	
	
	LIBGUI::VBox SystemWidget ( MainWindow, SYSTEMWIDGET);
	LIBGUI::VBox TerrariumWidget ( MainWindow, TERRARIUMWIDGET);
	LIBGUI::VBox MusicWidegt ( MainWindow, MUSICWIDEGT);
	LIBGUI::VBox InfoWidget ( MainWindow, INFOWIDGET);
	
	LIBGUI::HBox HBox_MusicPlay ( &MusicWidegt, "aHBox_MusicPlay");
	LIBGUI::HBox HBox_MusicControl ( &MusicWidegt, "cHBox_MusicControl");
	LIBGUI::HBox HBox_RadioPlay ( &MusicWidegt, "bHBox_RadioPlay");
	LIBGUI::HBox HBox_VolumeControl ( &MusicWidegt, "dHBox_VolumeControl");
	
	LIBGUI::PushButton PlayMusicOrdered (&HBox_MusicPlay, "aPlayMusicOrdered");
	PlayMusicOrdered.LabelPressed ("In Reihe", 0, 0, 0);
	PlayMusicOrdered.LabelUnPressed ("In Reihe", 0, 0, 255);
	LIBGUI::PushButton PlayMusicRandom (&HBox_MusicPlay, "bPlayMusicRandom");
	PlayMusicRandom.LabelPressed ("Zufall", 0, 0, 0);
	PlayMusicRandom.LabelUnPressed ("Zufall", 0, 0, 255);
	LIBGUI::PushButton PlayRadioB (&HBox_RadioPlay, "bPlayRadioMDR");
	PlayRadioB.LabelPressed ("MDR Radio Sachsen Anhalt", 0, 0, 0);
	PlayRadioB.LabelUnPressed ("MDR Radio Sachsen Anhalt", 0, 0, 255);
	LIBGUI::PushButton PlayRadio (&HBox_RadioPlay, "aPlayRadioBrocken");
	PlayRadio.LabelPressed ("Radio Brocken", 0, 0, 0);
	PlayRadio.LabelUnPressed ("Radio Brocken", 0, 0, 255);
	LIBGUI::PushButton PlayPaus (&HBox_MusicControl, "bPlayPaus");
	PlayPaus.LabelPressed ("Play/Pause", 0, 0, 0);
	PlayPaus.LabelUnPressed ("Play/Pause", 0, 0, 255);
	LIBGUI::PushButton PlayPrev (&HBox_MusicControl, "aPlayPrev");
	PlayPrev.LabelPressed ("|<", 0, 0, 0);
	PlayPrev.LabelUnPressed ("|<", 0, 0, 255);
	LIBGUI::PushButton PlayNext (&HBox_MusicControl, "cPlayNext");
	PlayNext.LabelPressed (">|", 0, 0, 0);
	PlayNext.LabelUnPressed (">|", 0, 0, 255);
	LIBGUI::PushButton VolUp (&HBox_VolumeControl, "bVolUP");
	VolUp.LabelPressed ("V++", 0, 0, 0);
	VolUp.LabelUnPressed ("V++", 0, 0, 255);
	LIBGUI::PushButton VolDown (&HBox_VolumeControl, "aVolDown");
	VolDown.LabelPressed ("V--", 0, 0, 0);
	VolDown.LabelUnPressed ("V--", 0, 0, 255);
	
	MainWindow->GetRenderer()->SetDrawColor ( 205,102,29, 0 );
	while ( MainWindow->IsOpen() )
	{
		MainWindow->ProcessEvent();
		MainWindow->Update (  );
		MainWindow->Draw ();
	}
	return 0;
}
