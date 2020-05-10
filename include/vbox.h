#ifndef __LIBGUI_VBOX__
#define __LIBGUI_VBOX__

#include "widget.h"
#include <string>
#include "rect.h"
#include "video.h"
#include "renderer.h"
#include "event.h"
#include <map>

namespace LIBGUI {


class VBox : public Widget {
protected:
	std::map<std::string,Widget*> _Child;
	std::map<std::string,Rect> _ChildRect;
	int _ChildCount;
	bool _FixW;
	bool _FixH;
	
public:		
	VBox ( Widget *parent, std::string ID );
	
	Renderer* GetRenderer ( void );
	Rect	GetSize	( void );
	bool	AddChild	( Widget *child, std::string ID );
	bool ChangeChild ( std::string ID );
	void	ChangeSize	( Rect rect );
	void	ProcessEvent	( Event *event );
	bool	Draw	(void );
	void Update ( void );
	void	ChangeOffset( Point offset );
	Point	GetOffset	( void );
	bool		IsFixedH		( void ){return _FixH;}
	bool		IsFixedW		( void ){return _FixW;}
	

	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
	
};


}//namespace LIBGUI

#endif //__LIBGUI_VBOX__
