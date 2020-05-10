#ifndef __LIBGUI_COMMON_BUTTON__
#define __LIBGUI_COMMON_BUTTON__

#include "texture.h"
#include "widget.h"
#include "basicrendertext.h"

namespace LIBGUI {


class PushButton : public Widget {
protected:
	lowRenderText *_PressedLabel;
	lowRenderText *_UnPressedLabel;
	std::string _PressedTexture;
	std::string _UnPressedTexture;
	
	Rect _DrawDestRect;
	Rect _LabelRect;
	bool _IsPressed;
	bool _IsCheckable;
	bool _IsActive;

public:		
	PushButton ( Widget *parent, std::string ID );
	
	
	void MakeCheckable ( bool val );
	Renderer* GetRenderer ( void );
	Rect	GetSize	( void );
	bool	AddChild	( Widget *child, std::string ID );
	void	ChangeSize	( Rect rect );
	void		ProcessEvent	( Event *event );
	void	Update	( void );
	
	bool	Draw	(void );
	void LabelPressed ( std::string text, Uint8 r, Uint8 g, Uint8 b );
	void LabelUnPressed ( std::string text, Uint8 r, Uint8 g, Uint8 b );
	void	ChangeOffset( Point offset );
	Point	GetOffset	( void );
	bool ChangeChild ( std::string ID );
	bool		IsFixedH		( void ){}
	bool		IsFixedW		( void ){}
	

	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );

	void ( *onActivate )( void *data );
	void ( *onDeactivate )( void *data );
};



}//namespace LIBGUI


#endif //__LIBGUI_COMMON_BUTTON__
