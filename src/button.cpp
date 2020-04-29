/*
 * picture_widget.cpp
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
#include <spdlog/spdlog.h>


namespace LIBGUI {

cButton::cButton ( cWidget *parent, std::string label, std::string ID )
{
	_ID = ID;
	_parent = parent;
	_texture = nullptr;
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
	if ( event.type == KLICKED )
		onKlick();
	if ( event.type == HOLD )
		onPressed();
}

bool cButton::load ( void )
{
	_texture = IMG_LoadTexture ( _parent->getRenderer(), "/opt/sample/button.png" );
	if ( _texture == nullptr)
	{
		SPDLOG_ERROR ("Can't load Texture ({}): {}", _ID, SDL_GetError());
		return false;
	}
	SPDLOG_INFO ("Load Texture ({}) successfull", _ID);
	return true;
}

void cButton::draw ( void )
{
	SDL_RenderCopy ( _parent->getRenderer(), _texture, NULL, NULL );
}

SDL_Renderer* cButton::getRenderer ( void )
{
	_parent->getRenderer ();
}

cRect cButton::getMySize ( void )
{
	return _rect;
}

}
