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
	Rect rect = _Rect;
	Point off;
	_Child[ID] = child;
	_ChildOrder.push_back(ID);
	//TODO _ChildCount kann sicher ersetzt werden map.size() oder sowas
	rect.SetW ( _Rect.GetW() / _ChildOrder.size() );
	off.SetY ( _Offset.GetY() );

	//neue größe für jedes Element setzen
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		if ( v == 0 )
		{
			off.SetX ( _Offset.GetX());				
		}
		else
		{
			off.SetX ( _Offset.GetX() + ( rect.GetW()*v));
		}
		//LOG->DEBUG (LOG_CATEGORY_LIBGUI, "%s _Child:", element.first.c_str());
		
		_Child[_ChildOrder[v]]->ChangeSize (rect);
		_Child[_ChildOrder[v]]->ChangeOffset (off);
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI, "...Erfolgreich");
	return true;
}

bool TopBar::ChangeChild ( std::string ID )
{}

void TopBar::ChangeSize	( Rect rect )
{
	_Rect = rect;
	_Rect.SetH (_FixH);

    if ( _ChildOrder.size() > 0 )
	{
	    Rect tmp = _Rect;
	    tmp.SetW ( _Rect.GetW() / _ChildOrder.size() );
	    rect.SetH (_FixH);

	    for (int v = 0; v < _ChildOrder.size(); v++)
    	{
    		_Child[_ChildOrder[v]]->ChangeSize (tmp);
    	}
    }
}

void TopBar::ProcessEvent	( Event *event )
{
	event->data = _Parent;
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		Rect r = _Child[_ChildOrder[v]]->GetSize();
		Point p = _Child[_ChildOrder[v]]->GetOffset();
		r.SetX(p.GetX());
		r.SetY(p.GetY());
		if ( r.PointIsIn ( Point (event->X, event->Y)))
		{
			_Child[_ChildOrder[v]]->ProcessEvent (event);
		}
	}
}
	
bool TopBar::Draw	(void )
{
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		_Child[_ChildOrder[v]]->Draw ();
	}
	return true;
}

void TopBar::Update ( void )
{}

void TopBar::ChangeOffset( Point offset )
{
	_Offset = offset;

	if ( _ChildOrder.size() > 0 )
	{
		Point off = _Offset;
	    for (int v = 0; v < _ChildOrder.size(); v++)
	    {
	        if ( v == 0 )
		    {
			    off.SetX ( _Offset.GetX());
		    }
		    else
		    {
			    off.SetX ( _Offset.GetX() + ( _Rect.GetW()*v));
		    }
		    _Child[_ChildOrder[v]]->ChangeOffset (off);
		}
	}
}

Point	TopBar::GetOffset	( void )
{
	return _Offset;
}



}//namespace LIBGUI
