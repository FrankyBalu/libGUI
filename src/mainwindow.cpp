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


#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON
#include <iostream>
#include "../include/mainwindow.h"
#include "../include/rect.h"
#include "../include/event.h"
#include <spdlog/spdlog.h>

namespace LIBGUI{

cMainWindow::cMainWindow ( std::string ID )
{
	_init ( SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,480, SDL_WINDOW_SHOWN, ID );
}

cMainWindow::cMainWindow ( int posX, int posY, int width, int height, int flags, std::string ID )
{
	_init ( posX, posY, width, height, flags, ID);
}

void cMainWindow::_init ( int posX, int posY, int width, int height, int flags, std::string ID )
{
	_window		= nullptr;
	_renderer 	= nullptr;
	_child 		= nullptr;
	_isOpen 	= false;
	_ID			= ID;
	_rect.setPos ( 0, 0 );
	_rect.setSize ( width, height );
	_flags = flags;

	SPDLOG_INFO ( "Init SDL (Video + Audio)...." );
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0 )
	{
		SPDLOG_ERROR ( "....{}", SDL_GetError() );
		return;
	}
	SPDLOG_INFO ( "....successfull");

	//FIXME: Error handling
	IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP );

	_hold = false;
	_buttonDown = false;
	_startTime = 0;
	_klickTime = 70;
	_holdTime = 200;
	_xStart = 0;
	_xRel = 0;
	_xNow = 0;
	_yStart = 0;
	_yRel = 0;
	_yNow = 0;
	_sEvent.type = NOEVENT;
	_sType = NONE;
}


bool cMainWindow::open ( void )
{
    SDL_CreateWindowAndRenderer ( _rect.getWidth(), _rect.getHeight(), _flags, &_window, &_renderer);
    if ( _renderer == nullptr || _window == nullptr )
    {
    	SPDLOG_ERROR ( "Can't create window: {}", SDL_GetError() );
    	SPDLOG_ERROR ( "Flags: {}", _flags );
    	exit (-1);
    }
	else
	{
    	SPDLOG_INFO ( "Window successfull created" );
    	int w,h;
    	SDL_GetWindowSize(_window, &w, &h);
    	_rect.setWidth (w);
    	_rect.setHeight (h);

    	_isOpen = true;
    }
}


void cMainWindow::draw(  void )
{
	SDL_RenderClear ( _renderer );
	if ( _child != nullptr )
	{
		_child->draw( );
	}
	SDL_RenderPresent ( _renderer );
}

void cMainWindow::update ( sEvent event )
{
	_updateEvent ();
	if( _sEvent.type == QUIT )
    {
    	SPDLOG_DEBUG ("QUIT EVENT");
        _isOpen = false;
        return;
    }
    if ( _child != nullptr )
    {

    	_child->update ( _sEvent );
    }
}


bool cMainWindow::isOpen ( void )
{
	return _isOpen;
}


SDL_Renderer* cMainWindow::getRenderer ( void )
{
	if (!_isOpen)
	{
		SPDLOG_ERROR ("Window is not open");
		return nullptr;
	}
	return _renderer;
}

cRect cMainWindow::getMySize ( void )
{
	return _rect;
}

void cMainWindow::setSize ( cRect size )
{
}

bool cMainWindow::addChild ( cWidget* child )
{
	if ( child == nullptr)
		std::cout << "da ist der fehler\n";
	if ( _child != nullptr )
	{
		SPDLOG_ERROR ("Window has a child");
		return false;
	}
	std::cout <<"kind hinzugefügt\n";
	_child = child;
	_child->setSize ( _rect );
	return true;
}

void cMainWindow::setKlickTime ( Uint32 time )
{
	_klickTime = time;
}

void cMainWindow::setHoldTime ( Uint32 time )
{
	_holdTime = time;
}

void cMainWindow::_updateEvent ( void )
{
	if ( _sEvent.type == KLICKED )
    {
        _sEvent.type = NOEVENT;
    }
    if ( _buttonDown && _sType != NONE )
    {
        _sEvent.type = NOEVENT;
		_xRel = 0;
		_yRel = 0;
    }
    if ( _buttonDown && _sType == NONE && SDL_GetTicks()-_startTime > _klickTime )
    {
    	if ( _hold )
	    	_sEvent.type = NOEVENT;
		else
		{
			_sEvent.type = HOLD;
	    	_hold = true;
		}
	}


    while( SDL_PollEvent( &_event ) > 0 )
    {
    	if( _event.type == SDL_QUIT )
    	{
    		_sEvent.type = QUIT;
      	}
    	else if ( _event.type == SDL_MOUSEBUTTONDOWN )
    	{
    		_startTime = SDL_GetTicks();
      		_buttonDown = true;
      		SDL_GetMouseState( &_xStart, &_yStart );
      		_xNow = _xStart;
      		_yNow = _yNow;
    	}
    	else if ( _event.type == SDL_MOUSEBUTTONUP )
    	{
    		if ( SDL_GetTicks() - _startTime <= _klickTime )
      		{
        		_sEvent.type = KLICKED;
        		_startTime = 0;
      		}
      		_buttonDown = false;
      		_sType = NONE;
      		_xRel = 0;
      		_yRel = 0;
      		_xStart = 0;
      		_yStart = 0;
      		_startTime = 0;
			_hold = false;
    	}
    	else if  ( _buttonDown && _event.type == SDL_MOUSEMOTION )
    	{
      		SDL_GetMouseState( &_xNow, &_yNow );

      		if ( _sType == NONE )
      		{
        		if ( ( _yStart - _yNow ) > ( _xStart - _xNow ) )
				{
           			_sType = VERTICALSLIDE;
					_xNow = 0;
					_xStart = 0;
					_yRel = _yStart - _yNow;
				}
         		else
				{
           			_sType = HORIZONTALSLIDE;
					_yNow = 0;
					_yStart = 0;
					_xRel = _xStart - _xNow;
				}
      		}

			if (  _sType == VERTICALSLIDE )
      		{
        		if ( _yRel < -5 || _yRel > 5 )
        		{
					_sEvent.type = SLIDEVERTICAL;
				}
      		}
      		else if ( _sType == HORIZONTALSLIDE )
      		{
        		if ( _xRel < -5 || _xRel > 5 )
        		{
          			_sEvent.type = SLIDEHORIZONTAL;
        		}
			}
    	}
    }

	_sEvent.x = _xNow;
	_sEvent.y = _yNow;
  	_sEvent.relX = _xRel;
  	_sEvent.relY = _yRel;
}


}
