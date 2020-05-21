/*
 * pushbutton.h
 * Copyright (C) 2020 Frank Kartheuser <frank.kurbatsch@gmail.com>
 *
 * libGUI is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libGUI is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	
	bool isFixedSize;

public:		
	PushButton ( Widget *parent, std::string ID );
	PushButton ( Widget *parent, std::string ID, int width, int height );
	
	void MakeCheckable ( bool val );
	Renderer* GetRenderer ( void );
	Rect	GetSize	( void );
	bool	AddChild	( Widget *child, std::string ID );
	bool	AddChild	( Widget *child, std::string ID, int w, int h ){}
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
