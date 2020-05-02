/*
 * HBox.cpp
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
#include "../include/button.h"
#include "../include/event.h"
#include "../include/hbox.h"
#include <spdlog/spdlog.h>


namespace LIBGUI {

cHBox::cHBox ( cWidget *parent, std::string ID )
{
	_ID = ID;
	_parent = parent;
	_parent->addChild ( this );
	_count = 0;
}

void cHBox::setSize ( cRect size )
{
	_rect.setPos  ( size.getPosX (), size.getPosY () );
	_rect.setSize  ( size.getWidth (), size.getHeight() );
}


void cHBox::update ( sEvent event )
{
	for ( int i = 0; i < _count; i++)
	{
		if ( (_rects[i]->getPosX() < event.x &&
			 (_rects[i]->getPosX() + _rects[i]->getWidth()) > event.x) 
			)
		{
			_childs[i]->update (event);
		}
				
	}
}

void cHBox::draw ( void )
{
	for ( int i = 0; i < _count; i++)
	{
		_childs[i]->draw();
	}
}

SDL_Renderer* cHBox::getRenderer ( void )
{
	_parent->getRenderer ();
}

cRect cHBox::getMySize ( void )
{
	return _rect;
}

bool cHBox::addChild ( cWidget *child )
{
	_childs[_count]=child;
	_count++;
	int w;
	w = _rect.getWidth() / _count;
	cRect rect;
	rect.setPosX (_rect.getPosX());
	rect.setPosY (_rect.getPosY());
	rect.setWidth (w);
	rect.setHeight (_rect.getHeight());
	
	for ( int i = 0; i < _count; i++ )
	{
		_childs[i]->setSize ( rect );
		_rects[i] = new cRect ( rect.getPos(),rect.getWidth(), rect.getHeight() );
		rect.setPosX ( rect.getPosX()+rect.getWidth());
	}
	
}


void cHBox::changeSize ( cRect newSize )
{
}

}



