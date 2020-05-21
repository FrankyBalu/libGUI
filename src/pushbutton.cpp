/*
 * pushbutton.cpp
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
 
#include "../include/pushbutton.h"
#include "../include/log.h"

#define DEFAULT_UNPRESSED_TEXTURE "/opt/sample/button.png"
#define DEFAULT_PRESSED_TEXTURE "/opt/sample/button2.png"
#define DEFAULT_TEXT_RED 255
#define DEFAULT_TEXT_GREEN 255
#define DEFAULT_TEXT_BLUE 255

namespace LIBGUI {

PushButton::PushButton ( Widget *parent, std::string ID )
{
		_ID = ID;		
		_Renderer = parent->GetRenderer();
		_UnPressedTexture = "DEFAULT_UNPRESSED_TEXTURE";
		_PressedTexture = "DEFAULT_PRESSED_TEXTURE";
		Texture::Inst()->Load ( DEFAULT_UNPRESSED_TEXTURE, _UnPressedTexture );
		Texture::Inst()->Load (  DEFAULT_PRESSED_TEXTURE, _PressedTexture );
		_Rect = parent->GetSize();
		_Parent = parent;
		
		_Offset = parent->GetOffset();
		_IsPressed = false;
		_DrawDestRect = _Rect;
		_DrawDestRect.SetX ( _Offset.GetX() );
		_DrawDestRect.SetY ( _Offset.GetY() );
		//berechnen label rect
		_LabelRect.SetH ( _Rect.GetH() * 0.9 );
		_LabelRect.SetW ( _Rect.GetW() * 0.9 );
		_LabelRect.SetX ( (_Rect.GetW()* 0.1 / 2) +_Offset.GetX() );
		_LabelRect.SetY ( (_Rect.GetH()* 0.1 / 2) +_Rect.GetH() );
		LOG->INFO (LOG_CATEGORY_LIBGUI, "_LabelRect: %s", ID.c_str());
		LOG->INFO (LOG_CATEGORY_LIBGUI, "   %d  %d  %d  %d", _LabelRect.GetX(),_LabelRect.GetY(),_LabelRect.GetW(),_LabelRect.GetH());
		
		parent->AddChild ( this, ID );
		onClick = nullptr;
		onPress = nullptr;
		onSlideH = nullptr;
		onSlideV = nullptr;
		onRelease = nullptr;
		onActivate = nullptr;
		onDeactivate = nullptr;	
		_IsCheckable = false;
		_IsActive = false;
		isFixedSize = false;
}


PushButton::PushButton ( Widget *parent, std::string ID, int width, int height )
{
		_ID = ID;		
		_Renderer = parent->GetRenderer();
		_UnPressedTexture = "DEFAULT_UNPRESSED_TEXTURE";
		_PressedTexture = "DEFAULT_PRESSED_TEXTURE";
		Texture::Inst()->Load ( DEFAULT_UNPRESSED_TEXTURE, _UnPressedTexture );
		Texture::Inst()->Load (  DEFAULT_PRESSED_TEXTURE, _PressedTexture );
		_Rect = parent->GetSize();
		_Parent = parent;
		
		_Offset = parent->GetOffset();
		_IsPressed = false;
		_DrawDestRect = _Rect;
		_DrawDestRect.SetX ( _Offset.GetX() );
		_DrawDestRect.SetY ( _Offset.GetY() );
		//berechnen label rect
		_LabelRect.SetH ( _Rect.GetH() * 0.9 );
		_LabelRect.SetW ( _Rect.GetW() * 0.9 );
		_LabelRect.SetX ( (_Rect.GetW()* 0.1 / 2) +_Offset.GetX() );
		_LabelRect.SetY ( (_Rect.GetH()* 0.1 / 2) +_Rect.GetH() );
		LOG->INFO (LOG_CATEGORY_LIBGUI, "_LabelRect: %s", ID.c_str());
		LOG->INFO (LOG_CATEGORY_LIBGUI, "   %d  %d  %d  %d", _LabelRect.GetX(),_LabelRect.GetY(),_LabelRect.GetW(),_LabelRect.GetH());
		
		parent->AddChild ( this, ID, width, height );
		if ( width > 0 )
			_Rect.SetW ( width );
		if ( height > 0 )
			_Rect.SetH ( height );
		onClick = nullptr;
		onPress = nullptr;
		onSlideH = nullptr;
		onSlideV = nullptr;
		onRelease = nullptr;
		onActivate = nullptr;
		onDeactivate = nullptr;	
		_IsCheckable = false;
		_IsActive = false;
		isFixedSize = true;
}
Renderer* PushButton::GetRenderer ( void )
{
	return _Renderer;
}

void PushButton::MakeCheckable ( bool val )
{
	_IsCheckable = val;
}

Rect	PushButton::GetSize	( void )
{
	return _Rect;
}
	
bool	PushButton::AddChild	( Widget *child, std::string ID )
{
	if ( child != nullptr)
			return false;//Buttons sollten keine Kinder haben
	return false;
}

void PushButton::ChangeSize ( Rect rect )
{
	if ( rect.GetW() <= 0 )
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Neue Breite von %s unter 0 (%d)", _ID.c_str(),rect.GetW() );	
		//_Rect.SetW (1);
	}
	else
	{
		_Rect.SetW ( rect.GetW());
	}
	if ( rect.GetH() <= 0 )
	{
		LOG->WARN (LOG_CATEGORY_LIBGUI,"Neue Höhe von %s unter 0 (%d)", _ID.c_str(),rect.GetH() );	
		//_Rect.SetH (1);
	}
	else
	{
		_Rect.SetH ( rect.GetH ());
	}
	
	_LabelRect.SetH ( _Rect.GetH() * 0.9 );
	_LabelRect.SetW ( _Rect.GetW() * 0.9 );
	_DrawDestRect.SetW ( _Rect.GetW());
	_DrawDestRect.SetH ( _Rect.GetH());	
}

void PushButton::ChangeOffset ( Point offset )
{
	_Offset = offset;
	LOG->DEBUG (LOG_CATEGORY_LIBGUI, "Neues Offset von %s ist %dx%d", _ID.c_str(), offset.GetX(), offset.GetY());
	
	_DrawDestRect.SetX (offset.GetX());
	_DrawDestRect.SetY (offset.GetY());
	_LabelRect.SetX ( (_Rect.GetW()* 0.1 / 2) + offset.GetX() );
	_LabelRect.SetY ( (_Rect.GetH()* 0.1 / 2) + offset.GetY() );
			LOG->DEBUG (LOG_CATEGORY_LIBGUI, "_DrawDestRect   %s: %dx%d %dx%d", _ID.c_str(), _DrawDestRect.GetX(), _DrawDestRect.GetY(), _DrawDestRect.GetW(), _DrawDestRect.GetH() );
		LOG->DEBUG (LOG_CATEGORY_LIBGUI, "_LabelRect      %s: %dx%d %dx%d\n", _ID.c_str(), _LabelRect.GetX(), _LabelRect.GetY(), _LabelRect.GetW(), _LabelRect.GetH() );
		
}

Point PushButton::GetOffset ( void )
{
	return _Offset;
}

void PushButton::LabelPressed ( std::string text, Uint8 r, Uint8 g, Uint8 b )
{
	LOG->DEBUG (LOG_CATEGORY_LIBGUI, "Neues LabelPressed erstellt: %s", text.c_str());
	_PressedLabel = basicRenderText::Inst()->Render ( text, r, g, b );
}

void PushButton::LabelUnPressed ( std::string text, Uint8 r, Uint8 g, Uint8 b )
{
	LOG->DEBUG (LOG_CATEGORY_LIBGUI, "Neues LabelUnPressed erstellt: %s", text.c_str());
	_UnPressedLabel = basicRenderText::Inst()->Render ( text, r, g, b );
}

bool	PushButton::Draw	(void )
{	
	if ( _IsPressed || _IsActive )
	{
		Texture::Inst()->Draw ( _PressedTexture, &_Rect, &_DrawDestRect );	
		Texture::Inst()->Draw ( _PressedLabel->ID, &_UnPressedLabel->Size, &_LabelRect );
	}
	else //if ( !_IsPressed || !_IsActive )
	{
		Texture::Inst()->Draw ( _UnPressedTexture, &_Rect, &_DrawDestRect );	
		Texture::Inst()->Draw ( _UnPressedLabel->ID, &_UnPressedLabel->Size, &_LabelRect );
	}
	return true;
}

void PushButton::ProcessEvent ( Event *event )
{
	if ( (event->Type == MOUSEBUTTONDOWN) || (event->Type == FINGERDOWN) )
	{
		if ( onPress != nullptr )
			onPress ( nullptr );
		_IsPressed = true;
		std::cout << _ID.c_str() << " clicked\n";
					
	}
	if ( event->Type == MOUSEBUTTONUP || (event->Type == FINGERUP))
	{
		if ( event->Clicks == 1 )
		{
			if ( _IsCheckable )
			{
				if ( _IsActive )
				{
					_IsActive = false;
					if ( onDeactivate != nullptr )
						onDeactivate ( nullptr );
				}
				else
				{
					_IsActive = true;
					if ( onActivate != nullptr )
						onActivate ( nullptr );
				}
			}
			else
			{
				if ( onClick != nullptr )
				{
					onClick(event->data);
				}
			}
		}
		else if ( onRelease != nullptr )
				onRelease(nullptr);
		_IsPressed = false;
	}		
}

void PushButton::Update ( void )
{

}

bool PushButton::ChangeChild ( std::string ID ){}


}//namespace LIBGUI
