#ifndef __LIBGUI_RECT__
#define __LIBGUI_RECT__

#include "point.h"
#include <SDL2/SDL.h>

namespace LIBGUI {

class Rect : public Point {
protected:
	int _w, _h;
	
public:
	Rect ( void );
	Rect ( Point p, int w, int h );
	Rect ( int x, int y, int w, int h );
	
	~Rect();
	
	
	int GetW ( void );
	int GetH ( void );
	
	void SetW ( int w );
	void SetH ( int h );
	void SetSize ( int w, int h );
	
	
	/**
	 * \brief Überprüft ob sich der angegebene Punkt im Rect befindet
	 */
	bool PointIsIn ( Point p );
	
	/**
	 * \brief Überprüft ob dieses Rect und das das als paramerer angegebene Rect
	 *			überschneiden
	 *
	 * \return true wenn es einen Schnittpunkt gibt, sonst false
	 */
	bool HasIntersection ( Rect& r );
	
	//Rect &operator= ( const Point &rhs);
	Rect &operator= ( const Rect &rhs);
	bool operator==(const Rect& rhs);

};

} //namespace LIBGUI

#endif //__LIBGUI_RECT__
