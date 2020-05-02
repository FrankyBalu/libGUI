/*
 * button.cpp
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
#include <spdlog/spdlog.h>

#include "../include/rect.h"
#include "../include/event.h"
#include "../include/mainwindow.h"
#include "../include/button.h"

namespace LIBGUI {


cButton::cButton ( cWidget *parent, std::string label, std::string ID )
{
	_ID 		= ID;
	_parent 	= parent;
	_texture 	= nullptr;
	_parent->addChild ( this );
	load ();
}

void cButton::setSize ( cRect size )
{
	_rect.setPos  ( size.getPosX (), size.getPosY () );
	_rect.setSize  ( size.getWidth (), size.getHeight() );
}


void cButton::update ( sEvent event )
{
	if ( event.down )
	{
		_texture = _tex2;
	}
	else
	{
		_texture = _tex1;
	}
	if ( event.type == KLICKED )
	{
			onKlick ();
	}
	if ( event.type == HOLD )
	{
			onPressed();
	}
}

bool cButton::load ( void )
{
	_tex1 = IMG_LoadTexture ( _parent->getRenderer(), "/opt/sample/button.png" );
	if ( _tex1 == nullptr)
	{
		SPDLOG_ERROR ("Can't load Texture ({}): {}", _ID, SDL_GetError());
		return false;
	}
	_tex2 = IMG_LoadTexture ( _parent->getRenderer(), "/opt/sample/button2.png" );
	if ( _tex2 == nullptr)
	{
		SPDLOG_ERROR ("Can't load Texture ({}): {}", _ID, SDL_GetError());
		return false;
	}
	SPDLOG_INFO ("Load Texture ({}) successfull", _ID);
	_texture = _tex1;
	return true;
}

void cButton::draw ( void )
{
	SDL_Rect rect;
	rect.x = _rect.getPosX();
	rect.y = _rect.getPosY();
	rect.h = _rect.getHeight();
	rect.w = _rect.getWidth();
	SDL_RenderCopy ( _parent->getRenderer(), _texture, NULL, &rect );
}

SDL_Renderer* cButton::getRenderer ( void )
{
	_parent->getRenderer ();
}

cRect cButton::getMySize ( void )
{
	return _rect;
}

void cButton::changeSize ( cRect rect )
{
	_rect.setPos ( rect.getPosX(), rect.getPosY());
	_rect.setSize ( rect.getWidth(), rect.getHeight());
}


}
