#ifndef __LIBGUI_WINDOW__
#define __LIBGUI_WINDOW__

#include "video.h"
#include "event.h"
#include "widget.h"
#include "topbar.h"
#include <map>


namespace LIBGUI {

  
class Window : public Widget
{
private:
    RawWindow *_Window;
    std::map <std::string,Widget*> _Child;
    Widget *_MainChild;
    TopBar *_Topbar;
    std::string _MainChildID;
    bool _IsOpen;
    Event 		_Event;

    
public:
	Window ( std::string title, int x, int y, int w, int h, unsigned int flags, std::string ID );
	//~Window ( void );
	~Window ( void );
	bool		IsOpen				( void );
		
	Renderer* 	GetRenderer 	( void );
	Rect		GetSize			( void );
	Point		GetOffset		( void );
    bool		AddChild		( Widget *child, std::string ID );
	bool		ChangeChild 	( std::string ID );
	void		ChangeSize		( Rect rect );
	void		ChangeOffset	( Point offset );
	void		ProcessEvent	( Event *event = nullptr );
	void		Update			( void );
	bool		Draw			( void );
	bool		IsFixedH		( void ){}
	bool		IsFixedW		( void ){}
	Widget*     GetTopbar		( void );
	
	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
  
  
    
  
};



}//namespace LIBGUI
#endif //__LIBGUI_WINDOW__
