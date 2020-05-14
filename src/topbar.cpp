/*
 * topbar.cpp
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
 
#include "../include/topbar.h"
#include "../include/log.h"

namespace LIBGUI {

TopBar::TopBar ( Widget *parent, std::string ID, int height )
{
	_ID = ID;
	_Parent = parent;
	_Renderer = _Parent->GetRenderer();
	_ChildCount = 0;
	_Rect.SetH ( height );
	_FixH = height;
	_Parent->AddChild( this, ID );
}
	
Renderer* TopBar::GetRenderer ( void )
{
	return _Renderer;
}

Rect TopBar::GetSize	( void )
{
	return _Rect;
}

bool TopBar::AddChild	( Widget *child, std::string ID )
{
	if ( _Child.count (ID) > 0)
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Ein Widget mit der ID: %s gibt es schon im Fenster: %s", ID.c_str(), _ID.c_str());
		return false;
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI, "Füge (%s) zu VBox (%s) hinzu", ID.c_str(), _ID.c_str());
	Rect rect;
	rect = _Rect;
	Point off;
	_Child[ID] = child;
	//TODO _ChildCount kann sicher ersetzt werden map.size() oder sowas
	rect.SetW ( _Rect.GetW() / (_ChildCount +1) );
	off.SetY ( _Offset.GetY() );
	int i = 0;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		if ( i == 0 )
		{
			off.SetX ( _Offset.GetX());				
		}
		else
		{
			off.SetX ( _Offset.GetX() + ( rect.GetW()*i));
		}
		LOG->DEBUG (LOG_CATEGORY_LIBGUI, "%s _Child:", element.first.c_str());
		std::cout << element.first << " X: " << off.GetX()<< " Y: " << off.GetY()<< " W: " << rect.GetW()<< " H: " << rect.GetH() << std::endl;
		element.second->ChangeSize (rect);
		element.second->ChangeOffset (off);
		_ChildRect[element.first].SetX (off.GetX());
		_ChildRect[element.first].SetW (rect.GetW());
		_ChildRect[element.first].SetH (rect.GetH());
		i++;
		
	}
	_ChildCount++;
	LOG->INFO (LOG_CATEGORY_LIBGUI, "...Erfolgreich");
	return true;
}

bool TopBar::ChangeChild ( std::string ID )
{}

void TopBar::ChangeSize	( Rect rect )
{
	_Rect = rect;
	Rect rec = rect;
	rect.SetW ( _Rect.GetW() / (_ChildCount +1) );
	rect.SetH (_FixH);
	_Rect.SetH (_FixH);
	
	int i = 0;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		std::cout << "chanegSize: " << element.first <<  " W: " << rect.GetW()<< " H: " << rect.GetH() << std::endl;
		
		element.second->ChangeSize (rec);
		_ChildRect[element.first].SetW (rec.GetW());
		i++;
	 }
}

void TopBar::ProcessEvent	( Event *event )
{
	event->data = _Parent;
	for (std::pair<std::string,Widget*> element : _Child)
	{
		if ( _ChildRect[element.first].PointIsIn ( Point (event->X, event->Y)))
		{
			element.second->ProcessEvent (event);
		}
	}
}
	
bool TopBar::Draw	(void )
{
	for (std::pair<std::string,Widget*> element : _Child)
	{
		//std::cout << "Draw " << element.first << std::endl;
		element.second->Draw ();
	}
	return true;
}

void TopBar::Update ( void )
{}

void TopBar::ChangeOffset( Point offset )
{
	_Offset = offset;
	Point off;
	off.SetY ( _Offset.GetY() );
	int i = 0;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		if ( i == 0 )
		{
			off.SetX ( _Offset.GetX());				
		}
		else
		{
			off.SetX ( _Offset.GetX() + ( _Rect.GetW()*i));
		}
		std::cout << "ChanegOffset: " <<element.first << " X: " << off.GetX()<< " Y: " << off.GetY() << std::endl;
		
		element.second->ChangeOffset (off);
		_ChildRect[element.first].SetX (off.GetX());
		i++;
	 }
}

Point	TopBar::GetOffset	( void )
{
	return _Offset;
}



}//namespace LIBGUI
