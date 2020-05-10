#ifndef __LIBGUI_TBOX__
#define __LIBGUI_TBOX__

#include <string>
#include "rect.h"
#include "video.h"
#include "renderer.h"
#include "event.h"
#include <map>

namespace LIBGUI {


class TBox : public Widget {
protected:
	std::map<int,Widget*> _child;
	std::map<int,Rect> _childRect;
	int _count;
    Widget *_mChild;
public:		
	TBox ( Widget *parent, std::string ID )
	{
		_ID = ID;
		_parent = parent;
		_parent->AddChild( this );
		_renderer = _parent->GetRenderer();
		_window = _parent->GetWindow();
		_count = 0;
		
	}
	
	pRenderer* GetRenderer ( void )
	{
		return _renderer;
	}
	Rect	GetSize	( void )
	{
		return *_rect;
	}
	pWindow* GetWindow ( void )
	{
		return _window;
	}
	bool	AddChild	( Widget *child )
	{
			Rect rect;
			rect = *_rect;
			Point off;

			_child[_count] = child;
			//teilen durch null verhindern
			if ( _count == 0)
			{
                rect.setH ( 40 );
			//	std::cout << "Rect höhe auf " << rect.getH() << " gesetzt\n";
			}
			else
			{
				rect.setH  (_rect->getH()-40);
				//std::cout << "Rect höhe auf " << rect.getH() << " gesetzt\n";
			}

			off.setX ( _offset.getX() );
			
			
			int f;	
			if ( _count != 0 )	
					off.setY (_offset.getY() +  40);
			else
				 	off.setY (_offset.getY());
			
        for ( int mn =  0; mn<_count; mn++){
				_childRect[mn] = rect;
				//std::cout << "neues Rect:\n";
				//std::cout << "X: "<< rect.getX() << " Y: " << rect.getY() << " W: " << rect.getW() << " H: " << rect.getH()<< std::endl;
				//std::cout << "OX: " << off.getX() << " OY: " << off.getY() << std::endl;
				_child[mn]->ChangeSize ( &_childRect[mn] );
				_child[mn]->ChangeOffset ( off );
        }	
			_count++;
        
	}
	void	ChangeSize	( Rect *rect )
	{
		_rect = rect;
	}
	bool	Update	( Event *event )
	{
			for ( int i = 0; i <_count; i++)
			{
				Rect r = _childRect[i];
				Point p = _child[i]->GetOffset();
				r.setX ( p.getX() );
				r.setY ( p.getY() );

				if ( (event->type == MOUSEBUTTONDOWN) || (event->type == FINGERDOWN) )
				{
					if ( r.pointIsIn( Point (event->button.x,event->button.y )))
					{
						
						_child[i]->Update (event);
					}
				}
				if ( event->type == MOUSEBUTTONUP || (event->type == FINGERUP))
				{
					if ( r.pointIsIn( Point (event->button.x,event->button.y )))
					{
						_child[i]->Update (event);
					}
				}
			}
	}
	bool	Draw	(void )
	{
		for ( int i = 0; i < _count; i++ )
		{
			_child[i]->Draw();
		}
	}
	void	ChangeOffset( Point offset )
	{
		_offset = offset;
		//std::cout << "Offset auf " << _offset.getX() << "x" << _offset.getY() <<std::endl;
	}
	Point	GetOffset	( void )
	{
		return _offset;
	}

	void ( *onKlick )	( void *data );
	void ( *onPressed )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
	
};


}//namespace LIBGUI

#endif //__LIBGUI_VBOX__
