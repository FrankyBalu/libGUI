/*
 * header.h
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


class cPoint {
private:
	int _x;
	int _y;
public:
	cPoint ();
	cPoint ( int x, int y);
	~cPoint ();
	
	void setPosX ( int x );
	void setPosY ( int y );
	void setPos  ( int x, int y);
	
	int getPosX ( void );
	int getPosY ( void );
};

class cRect {
private:
	cPoint _point;
	int _width;
	int _height;
	
public:
	cRect ( void );
	cRect ( int x, int y, int width=1, int height=1 );
	cRect ( cPoint point, int width=1, int height=1 );
	
	void setPosX ( int x );
	void setPosY ( int y );
	void setPos  ( int x, int y );
	void setPos  ( cPoint point );
	void setWidth ( int width );
	void setHeight ( int height );
	void setSize  ( int width, int height );
	
	cPoint getPos ( void );
	int getPosX ( void );
	int getPosY ( void );
	int getHeight ( void );
	int getWidth ( void );
	
};
	
