/*
 * mainwindow.cpp
 * Copyright (C) 2020 Frank Kurbatsch <frank.kurbatsch@gmail.com>
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
#include <iostream>
#include "../include/event.h"

namespace LIBGUI {

cSysEvent::cSysEvent ( void )
{
    //_event = new SDL_Event;

    _type = ENONE;
    _xStart = 0;
    _yStart = 0;
    _timeStart = 0;
    _klickTime = 70;
    _xRel = 0;
    _yRel = 0;
    _xNow = 0;
    _yNow = 0;
    _buttonDown = false;
    _slide = 0;
    _isPressed = 0;
}

cSysEvent::~cSysEvent( void )
{
    //free ( _event );
}


bool cSysEvent::update ( void )
{
	std::cout << "Event Update: -5\n";
    if (_type == KLICK )
    {
        _type = ENONE;
        std::cout << "Event Update: -4\n";
    }
    if ( _buttonDown && _slide != 0 )
    {
        _type = ENONE;
		_xRel = 0;
		_yRel = 0;
		std::cout << "Event Update: -3\n";
    }
    if ( _buttonDown && _slide == 0 && SDL_GetTicks()-_timeStart > _klickTime )
    {
    	std::cout << "Event Update: -2\n";
		if ( _isPressed )
	    	_type = ENONE;
		else
		{
			std::cout << "Event Update: -1\n";
      	    _type = PRESSED;
	    	_isPressed = true;
		}
	std::cout << "Event Update: 0\n";
    }
    std::cout << "Event test Update: 1\n";

    //while( SDL_PollEvent( &_event ) > 0 )
    SDL_PollEvent ( &_event );
    {
    std::cout << "Event test Update: " << SDL_GetError ()<<std::endl;

    		if( _event.type == SDL_QUIT )
    		{
    			std::cout << "Event Update: 1\n";
      			_type = QUIT;
      			//return true;
    		}
    		else if ( _event.type == SDL_MOUSEBUTTONDOWN )
    		{
    			std::cout << "Event Update: 2\n";
      			_timeStart = SDL_GetTicks();
      			_buttonDown = true;
      			SDL_GetMouseState( &_xStart, &_yStart );
    		}
    		else if ( _event.type == SDL_MOUSEBUTTONUP )
    		{
    			std::cout << "Event Update: 3\n";
      			if ( SDL_GetTicks() - _timeStart <= _klickTime )
      			{
        			_type = KLICK;
        			_timeStart = 0;
      			}
      			_buttonDown = false;
      			_slide = 0;
      			_xRel = 0;
      			_yRel = 0;
      			_xNow = 0;
      			_yNow = 0;
      			_timeStart = 0;
			_isPressed = false;
    		}
    		else if  ( _buttonDown && SDL_MOUSEMOTION )
    		{
    			std::cout << "Event Update: 4\n";
    		    int x, y, x1, y1;
      			SDL_GetMouseState( &x, &y );

      			_xNow = _xStart-x;

				_yNow = _yStart-y;

      			if ( _slide == 0 )
      			{
         			if ( _yNow > _xNow )
				{
           				_slide = 1;
					_xNow = 0;
				}
         			else
				{
           				_slide = 2;
					_yNow = 0;
				}
      			}

				if (  _slide == 1 )
      			{
        			if ( _yRel != _yNow )
        			{
						_yRel = _yNow;
          				_type = SLIDEVERTICAL;
					}
      			}
      			else if ( _slide == 2 )
      			{
        			if ( _xRel != _xNow )
        			{
						_xRel = _xNow;
          				_type = SLIDEHORIZONTAL;
        			}
				}
    		}
    		std::cout << "Event Update: 5\n";
	}
}

EVENTTYPE cSysEvent::getType ( void )
{
  return _type;
}

int cSysEvent::getX ( void )
{
  return _xStart;
}

int cSysEvent::getY ( void )
{
  return _yStart;
}

int cSysEvent::getSlideH ( void )
{
  if ( _slide == 0 )
      return 0;
  else
      return _xRel;
}

int cSysEvent::getSlideV ( void )
{
  if ( _slide == 0 )
      return 0;
  else
      return _yRel;
}

void cSysEvent::setKlickTime ( Uint32 time )
{
  _klickTime = time;
}

sEvent cSysEvent::getSEvent ( void )
{
    sEvent ev;
    ev.type = _type;
    ev.x = _xStart;
    ev.y = _yStart;
    ev.relX = _xRel;
    ev.relY = _yRel;
    return ev;
}

}
