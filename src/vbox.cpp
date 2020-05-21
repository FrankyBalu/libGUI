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



void VBox::Init ( Widget *parent, std::string ID, int width, int height )
{
	if ( !parent->AddChild ( this, ID ) )
	{
	//	LOG->ERROR (LOG_CATEGORY_LIBGUI,"Ein Widget mit der ID: %s gibt es schon im Widget: %s", ID.c_str(), parent->GetID().c_str());
		return;
	}
	
	_ID = ID;
	_Parent = parent;
	_Renderer = _Parent->GetRenderer();
	_ChildCount = 0;
	_FixedSizeChildCount = 0;
	_FixedHeightAll = 0;
	if ( width > 0 )
		_FixedWidth = width;
	else
		_FixedWidth = -11;//FIXME statt -11 sollte eine konstante eingefügt werden
	if ( height > 0 )
		_FixedHeight = height;
	else
		_FixedHeight = -11;//FIXME statt -11 sollte eine konstante eingefügt werden
}


VBox::VBox ( Widget *parent, std::string ID )
{
	Init ( parent, ID, -1, -1 );
}

VBox::VBox ( Widget *parent, std::string ID, int width, int height )
{
	Init ( parent, ID, width, height );
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
	AddChild ( child, ID, -1, -1 );
}

bool VBox::AddChild ( Widget *child, std::string ID, int width, int height )
{
	//Wenn ID schon vergeben, kann das Widget nicht hinzugefügt werden
	if ( _Child.count (ID) > 0)
	{
		LOG->ERROR (LOG_CATEGORY_LIBGUI,"Ein Widget mit der ID: %s gibt es schon im Widget: %s", ID.c_str(), _ID.c_str());
		return false;
	}
	//Info das ein Widget hinzugefügt wird
	LOG->INFO (LOG_CATEGORY_LIBGUI, "Füge (%s) zu VBox (%s) hinzu", ID.c_str(), _ID.c_str());
	
	//Die größen für die rects
	Rect rect = _Rect;
	Rect dynRect = _Rect;
	
	//Passt das neue widget überhaupt rein
	if ( width > 0 )
	{
		if ( _Rect.GetW() < width )
		{
			LOG->ERROR (LOG_CATEGORY_LIBGUI,"\tWidget %s ist zubreit für %s", ID.c_str(), _ID.c_str());
			return false;
		}
	}
	if ( height > 0 )
	{
		if ( ( _Rect.GetH() - _FixedHeightAll ) < height )
		{
			LOG->ERROR (LOG_CATEGORY_LIBGUI,"\tWidget %s ist hoch für %s", ID.c_str(), _ID.c_str());
			return false;
		}
		_ChildIsFixed[ID] = true;
		//Größe des neuen widgets setzen
		rect.SetH ( height );
		child->ChangeSize ( rect );
		_FixedSizeChildCount++;
		_FixedHeightAll += height;
	}
	else
	{
		_ChildIsFixed[ID] = false;
		_ChildCount++;
	}
	
	
	Point offset;
	_Child[ID] = child;
	_ChildOrder.push_back(ID);
	
	if ( _ChildCount > 0)
	{
		dynRect.SetH ( ( _Rect.GetH() - _FixedHeightAll ) / _ChildCount );
		std::cout << "\t\tdynRect.SetH ( ( " << dynRect.GetH() << " - " << _FixedHeightAll << " ) / " << _ChildCount << std::endl;
	}
	offset.SetX ( _Offset.GetX() );
	int realOffset;
	std::cout << "dynrect h: " << dynRect.GetH() << std::endl;
	//neue größe für jedes Element setzen
	for (int i = 0; i < _ChildOrder.size(); i++)
	{
		if ( i == 0 )
		{
			offset.SetY ( _Offset.GetY() );
			realOffset = _Offset.GetY();
			if ( _ChildIsFixed[_ChildOrder[i]] )
			{
				Rect r = _Rect;
				r.SetH ( -1 );
				_Child[_ChildOrder[i]]->ChangeSize ( r );
				realOffset += _Child[_ChildOrder[i]]->GetSize().GetH();
				//_FixedHeightAll += _Child[_ChildOrder[i]]->GetSize().GetH();
			}
			else
			{
				_Child[_ChildOrder[i]]->ChangeSize ( dynRect );
				realOffset += dynRect.GetH();
				_ChildCount++;
			}
			_Child[_ChildOrder[i]]->ChangeOffset ( offset );
		
		}
		else
		{
			if ( _ChildIsFixed[_ChildOrder[i]] )
			{
				Rect r = _Rect;
				r.SetH ( -1 );
				_Child[_ChildOrder[i]]->ChangeSize ( r );
				realOffset += _Child[_ChildOrder[i]]->GetSize().GetH();
				//_FixedHeightAll += _Child[_ChildOrder[i]]->GetSize().GetH();
			}
			else
			{
				_Child[_ChildOrder[i]]->ChangeSize ( dynRect );
				realOffset += dynRect.GetH();
			}
			_Child[_ChildOrder[i]]->ChangeOffset ( offset );
		
		}
		offset.SetY ( realOffset );
		std::cout << "\tVBox " << _ID << " Widget " << _ChildOrder[i] << std::endl;
		if ( _ChildIsFixed[_ChildOrder[i]] )
		{
			std::cout << "Fixed Size W: " << _Child[_ChildOrder[i]]->GetSize().GetW();
			std::cout << "Fixed Size H: " << _Child[_ChildOrder[i]]->GetSize().GetH();
		}
		else
		{
			std::cout << "Dyn Size W: " << _Child[_ChildOrder[i]]->GetSize().GetW();
			std::cout << "Dyn Size H: " << _Child[_ChildOrder[i]]->GetSize().GetH();
		}
		std::cout << "\tX: " << offset.GetX () << " Y: " << offset.GetY () << std::endl; 
		
		std::cout << "vbox 5\n";
	
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
