#ifndef __LIBGUI_POINT__
#define __LIBGUI_POINT__


namespace LIBGUI {


class Point {
protected:
	int _x, _y;

public:
	Point ( void );
	Point ( int x, int y );
	
	~Point ( void );
	
	int GetX ( void );
	int GetY ( void );
	
	void SetX ( int x );
	void SetY ( int y );
	void Set ( int x, int y );
	
	
	
	Point &operator= ( const Point &rhs);
	bool operator==(const Point& rhs);

};


}//namespace LIBGUI

#endif //__LIBGUI_POINT__
