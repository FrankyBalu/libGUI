/*
 * window.cpp
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
 
#include "../include/window.h"
#include "../include/log.h"
#include <iostream> 
#include <algorithm>


namespace LIBGUI {




Window::Window ( std::string title, int x, int y, int w, int h, unsigned int flags, std::string ID )
{
		_Window = lowVideo::Inst()->CreateWindow ( title.c_str(), x, y, w, h, flags );
		if (_Window == nullptr)
		{
			_IsOpen = false;
			return;
		}
		_Renderer = new Renderer ( _Window );
		if (_Renderer == nullptr)
		{
			_IsOpen = false;
			return;
		}	
		_ID = ID;
		_Parent = nullptr;
		_MainChild = nullptr;
		int tmpW, tmpH;
		lowVideo::Inst()->GetWindowSize ( _Window, &tmpW, &tmpH );
		_Rect.SetX (0);
		_Rect.SetY (0);
		_Rect.SetSize (tmpW, tmpH);
		_Offset.SetX(0);
		_Offset.SetY(0);
		_IsOpen = true;	
		_MainChild = nullptr;
		_Topbar = new TopBar ( this, "WINDOWTOPBAR", 40 );	
//		_Rect.SetY ( 40 );
		_Offset.SetY(40);
		_Rect.SetH ( _Rect.GetH() - 40);
		_Event.Type		= NOEVENT;
		_Event.WindowID = 0;
		_Event.NewW		= 0;
		_Event.NewH		= 0;
		_Event.X		= 0;
		_Event.Y		= 0;
		_Event.XRel		= 0;
		_Event.YRel		= 0;
		_Event.x		= 0;
		_Event.y		= 0;
		_Event.xRel		= 0;
		_Event.yRel		= 0;
}

Window::~Window ( void )
{
	//FIXME hier muss noch was rein!!!
}

bool Window::IsOpen ( void )
{
	return _IsOpen;
}

Renderer* Window::GetRenderer ( void )
{
	return _Renderer;
}

Rect Window::GetSize ( void )
{
	return _Rect;
}


bool Window::AddChild ( Widget *child, std::string ID)
{
    /*if ( _ChildOrder.size() > 0)
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Ein Widget mit der ID: %s gibt es schon im Fenster: %s", ID.c_str(), _ID.c_str());
		return false;
	}*/
	_Child[ID] = child;
	_Child[ID]->ChangeSize ( _Rect );
	_Child[ID]->ChangeOffset ( _Offset );
	std::cout << "Window::AddChild 107\n";
	std::cout << "ChildOrder.size(): " << _ChildOrder.size() << std::endl;
	if (_MainChild == nullptr && ID != "WINDOWTOPBAR" )
	{
            _MainChild = child;
	        _MainChildID = ID;
	}
    //if ( ID != "WINDOWTOPBAR" )
    //{
    _ChildOrder.push_back(ID);
    //}
	    LOG->INFO ("Setze MainWidget von %s auf %s", _ID.c_str(), ID.c_str());

	LOG->INFO (LOG_CATEGORY_LIBGUI,"Widget (%s) zu Fenster (%s) hinzugefügt", ID.c_str(), _ID.c_str());
	return true;
}

bool Window::ChangeChild ( std::string ID)
{
    if ( _ChildOrder.size() <= 0)
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Widget (%s) gibt es nicht im Fenster: %s", ID.c_str(), _ID.c_str());
		return false;
	}
	else
	{
		LOG->INFO (LOG_CATEGORY_LIBGUI,"Wechsel MainWidget zu %s", ID.c_str());
		_MainChild = _Child[ID];
		_MainChildID = ID;
		return true;
	}
}


void Window::ChangeSize ( Rect rect )
{
	_Rect = rect;
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		_Child[_ChildOrder[v]]->ChangeSize (_Rect);
	}
}

void Window::ProcessEvent ( Event *event )
{
	if ( event != nullptr )
		return;
	lowEvent::Inst()->Update();
	_Event = lowEvent::Inst()->Get();
	if ( _Event.Type == WINDOWRESIZE )
	{
		int tmpW, tmpH;
		Rect rect;
		lowVideo::Inst()->GetWindowSize ( _Window, &tmpW, &tmpH );
		rect.SetSize ( tmpW, tmpH - 40);
		ChangeSize (rect);
		
		LOG->INFO (LOG_CATEGORY_LIBGUI,"Fenster größe von %s geändert: W = %d H = %d", _ID.c_str(), tmpW, tmpH);
		for (int v = 0; v < _ChildOrder.size(); v++)
		{
			_Child[_ChildOrder[v]]->ChangeSize (_Rect);
		}
	}
	else if ( _Event.Type != NOEVENT )
	{
		if ( _MainChild != nullptr && _Event.Y > 40 )
		{
			_MainChild->ProcessEvent ( &_Event );
		}
		else if ( _Event.Y < 40 )
			_Topbar->ProcessEvent (&_Event);
		if ( _Event.Type == QUIT )
		{
			LOG->INFO (LOG_CATEGORY_LIBGUI,"Fenster %s wird geschlossen", _ID.c_str());
			lowVideo::Inst()->DestroyWindow ( _Window );
			_IsOpen = false;
		}
	}
}

void Window::Update ( void )
{
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		_Child[_ChildOrder[v]]->Update ();
		//std::cout << "Widget Adresse von " << _ChildOrder[v] << ": " << _Child[_ChildOrder[v]] << std::endl;
		//std::cout << "Order size: "  << _ChildOrder.size() << std::endl;
	}
	
}

bool Window::Draw ( void )
{
	if ( _Renderer->Clear() != 0 )
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Fenster %s: Renderer konnte nicht resetet werden", _ID.c_str());
		return false;
	}
	if ( _MainChild != nullptr )
	{
		//std::cout << "draw: " << _MainChildID << std::endl;
		if ( !_MainChild->Draw() )
		{
			LOG->ERROR (LOG_CATEGORY_LIBGUI,"Fenster %s: Konnte %s nicht Rendern: %s", _ID.c_str(), _MainChildID.c_str());
			return false;
		}
		
	}
	_Topbar->Draw();
	_Renderer->Present();
	return true;
}

void Window::ChangeOffset ( Point offset )
{
	//TODO blödsinn... die Compilerwarnung muss auch anders weg gehen, denk ich mal
	offset.GetX();
}
Point	Window::GetOffset	( void )
{
	return Point (0,0);
}

Widget* Window::GetTopbar ( void )
{
	return _Topbar;
}



}//namespace LIBGUI
