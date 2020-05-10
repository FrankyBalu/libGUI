#include "../include/hbox.h"
#include "../include/log.h"

namespace LIBGUI {

HBox::HBox ( Widget *parent, std::string ID )
{
	_ID = ID;
	_Parent = parent;
	_Renderer = _Parent->GetRenderer();
	_ChildCount = 0;
	_FixW = false;
	_FixH = false;
	
	_Parent->AddChild( this, ID );
}
	
Renderer* HBox::GetRenderer ( void )
{
	return _Renderer;
}

Rect HBox::GetSize	( void )
{
	return _Rect;
}

bool HBox::AddChild	( Widget *child, std::string ID )
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

bool HBox::ChangeChild ( std::string ID )
{}

void HBox::ChangeSize	( Rect rect )
{
	Rect tmp = _Rect;
	_Rect = rect;
	Rect rec = rect;
	rect.SetW ( _Rect.GetW() / (_ChildCount +1) );
	
	int i = 0;
	//neue größe für jedes Element setzen
	for (std::pair<std::string,Widget*> element : _Child)
	{
		element.second->ChangeSize (rec);
		_ChildRect[element.first].SetW (rec.GetW());
		i++;
	 }
}

void HBox::ProcessEvent	( Event *event )
{
	event->data = _Parent;
			std::cout << "auch hier " << _ID.c_str() << std::endl;
	for (std::pair<std::string,Widget*> element : _Child)
	{
		std::cout << "auch hier 2" << _ID.c_str() << std::endl;
		if ( _ChildRect[element.first].PointIsIn ( Point (event->X, event->Y)))
		{
			std::cout << "auch hier 3" << _ID.c_str() << std::endl;
			element.second->ProcessEvent (event);
		}
	}
}
	
bool HBox::Draw	(void )
{
	for (std::pair<std::string,Widget*> element : _Child)
	{
		element.second->Draw ();
	}
	return true;
}

void HBox::Update ( void )
{}

void HBox::ChangeOffset( Point offset )
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
		element.second->ChangeOffset (off);
		_ChildRect[element.first].SetX (off.GetX());
		i++;
	 }
}

Point	HBox::GetOffset	( void )
{
	return _Offset;
}



}//namespace LIBGUI
