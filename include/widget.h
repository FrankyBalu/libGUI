#ifndef __LIBGUI_WIDGET__
#define __LIBGUI_WIDGET__

#include <string>
#include "rect.h"
#include "video.h"
#include "renderer.h"
#include "event.h"

namespace LIBGUI {


class Widget {
protected:
	std::string	_ID;
	Widget 		*_Parent;
	Renderer 	*_Renderer;
	Rect 		_Rect;
	Point 		_Offset;
	
	Widget(){}
	~Widget(){}
public:		
	virtual Renderer* 	GetRenderer 	( void ) = 0;
	virtual Rect		GetSize			( void ) = 0;
	virtual Point		GetOffset		( void ) = 0;
	
	virtual bool		AddChild		( Widget *child, std::string ID ) = 0;
	virtual bool		ChangeChild 	( std::string ID ) = 0;
	virtual void		ChangeSize		( Rect rect ) = 0;
	virtual void		ChangeOffset	( Point offset ) = 0;
	virtual void 		ProcessEvent	( Event *event ) = 0;
	virtual void		Update			( void ) = 0;
	virtual bool		Draw			( void ) = 0;
	virtual bool		IsFixedH		( void ) = 0;
	virtual bool		IsFixedW		( void ) = 0;
	

	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
};


}//namespace LIBGUI

#endif //__LIBGUI_WIDGET__
