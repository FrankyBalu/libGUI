#include "../include/vbox.h"
#include "../include/log.h"
#include <iostream>
namespace LIBGUI {


VBox::VBox ( Widget *parent, std::string ID )
{
	_ID = ID;
	_Parent = parent;
	_Renderer = _Parent->GetRenderer();
	_ChildCount = 0;
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
	//TODO _ChildCount kann sicher ersetzt werden map.size() oder sowas
	rect.SetH ( _Rect.GetH() / (_ChildCount +1) );
	off.SetX ( _Offset.GetX() );
	int i = 0;
	int h;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		if ( i == 0 )
		{
			off.SetY ( _Offset.GetY());				
		}
		else
		{
			off.SetY ( _Offset.GetY() + ( rect.GetH()*i));
		}
		LOG->DEBUG (LOG_CATEGORY_LIBGUI, "%s _Child:", element.first.c_str());
		element.second->ChangeSize (rect);
		element.second->ChangeOffset (off);
		_ChildRect[element.first].SetY (off.GetY());
		_ChildRect[element.first].SetW (rect.GetW());
		_ChildRect[element.first].SetH (rect.GetH());
		i++;
	}
	_ChildCount++;
	LOG->INFO (LOG_CATEGORY_LIBGUI, "...Erfolgreich");
	return true;
}

bool VBox::ChangeChild ( std::string ID )
{
}

void VBox::ChangeSize ( Rect rect )
{
	Rect tmp =_Rect;	
	_Rect = rect;
	Rect rec = rect;
	rect.SetH ( _Rect.GetH() / (_ChildCount +1) );
	
	int i = 0;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		element.second->ChangeSize (rec);
		_ChildRect[element.first].SetH (rec.GetH());
		i++;
	 }
}

void VBox::ProcessEvent ( Event *event )
{
	event->data = _Parent;
			std::cout << "auch hier " << _ID.c_str() << std::endl;
	for (std::pair<std::string,Widget*> element : _Child)
	{
		std::cout << "auch hier 2" << _ID.c_str() << std::endl;
		std::cout << "X:" << event->X << "x" << event->Y << std::endl;
		if ( _ChildRect[element.first].PointIsIn ( Point (event->X, event->Y)))
		{
			std::cout << "auch hier 3" << _ID.c_str() << std::endl;
			element.second->ProcessEvent (event);
		}
	}
}
	
bool VBox::Draw (void )
{
	for (std::pair<std::string,Widget*> element : _Child)
	{
		element.second->Draw ();
	}
	return true;
}

void VBox::Update ( void )
{}

void VBox::ChangeOffset ( Point offset )
{
	_Offset = offset;
	Point off;
	off.SetX ( _Offset.GetX() );
	int i = 0;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		if ( i == 0 )
		{
			off.SetY ( _Offset.GetY());				
		}
		else
		{
			off.SetY ( _Offset.GetY() + ( _Rect.GetH()*i));
		}
		element.second->ChangeOffset (off);
		_ChildRect[element.first].SetY (off.GetY());
		i++;
	 }
}

Point	VBox::GetOffset	( void )
{
	return _Offset;
}





}//namespace LIBGUI
