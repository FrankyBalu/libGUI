/*
 * vbox.cpp
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
 
#include "../include/vbox.h"
#include "../include/log.h"
#include <iostream>
namespace LIBGUI {


VBox::VBox ( Widget *parent, std::string ID )
{

	_ID = ID;
	_Parent = parent;
	_Renderer = _Parent->GetRenderer();
	//_ChildCount = 0;
	_FixW = false;
	_FixH = false;
	_Parent->AddChild( this, ID );
}
	
Renderer* VBox::GetRenderer ( void )
{
	return _Renderer;
}

Rect VBox::GetSize ( void )
{
	return _Rect;
}

bool VBox::AddChild ( Widget *child, std::string ID )
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
	_ChildOrder.push_back(ID);

	//TODO _ChildCount kann sicher ersetzt werden map.size() oder sowas
	rect.SetH ( _Rect.GetH() / _ChildOrder.size() );
	off.SetX ( _Offset.GetX() );
	//neue größe für jedes Element setzen
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		if ( v == 0 )
		{
			off.SetY ( _Offset.GetY());				
		}
		else
		{
			off.SetY ( _Offset.GetY() + ( rect.GetH()*v));
		}
		//LOG->DEBUG (LOG_CATEGORY_LIBGUI, "%s _Child:", element.first.c_str());
		_Child[_ChildOrder[v]]->ChangeSize (rect);
		_Child[_ChildOrder[v]]->ChangeOffset (off);
	}
	LOG->INFO (LOG_CATEGORY_LIBGUI, "...Erfolgreich");
	return true;
}

bool VBox::ChangeChild ( std::string ID )
{
}

void VBox::ChangeSize ( Rect rect )
{
	_Rect = rect;
	
	if ( _ChildOrder.size() > 0)
	{
	    Rect tmp =_Rect;
	    tmp.SetH ( _Rect.GetH() / _ChildOrder.size() );

    	for (int v = 0; v < _ChildOrder.size(); v++)
    	{
    		_Child[_ChildOrder[v]]->ChangeSize (tmp);
    	}
    }
}

void VBox::ProcessEvent ( Event *event )
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
	
bool VBox::Draw (void )
{
	for (int v = 0; v < _ChildOrder.size(); v++)
	{
		_Child[_ChildOrder[v]]->Draw ();
	}
	return true;
}

void VBox::Update ( void )
{}

void VBox::ChangeOffset ( Point offset )
{
	_Offset = offset;

	if ( _ChildOrder.size() > 0 )
	{
	    Point off = _Offset;
	    for (int v = 0; v < _ChildOrder.size(); v++)
	    {
		    if ( v == 0 )
	    	{
		    	off.SetY ( _Offset.GetY());
	    	}
		    else
	    	{
		    	off.SetY ( _Offset.GetY() + ( _Rect.GetH()*v));
	    	}
		    _Child[_ChildOrder[v]]->ChangeOffset (off);
	    }
	}
}

Point	VBox::GetOffset	( void )
{
	return _Offset;
}





}//namespace LIBGUI
