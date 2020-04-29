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
#include "../include/picture.h"
#include "../include/event.h"
#include <spdlog/spdlog.h>

namespace LIBGUI {

cPicture::cPicture ( cWidget* parent, std::string file, std::string id )
{
	_filePath = file;
	_ID = id;
	_parent = parent;
	_texture = nullptr;
	parent->addChild ( this );
}


void cPicture::update ( sEvent event )
{

}

bool cPicture::load ( void )
{
	_texture = IMG_LoadTexture ( _parent->getRenderer(), _filePath.c_str() );
	if ( _texture == nullptr)
	{
		SPDLOG_ERROR ("Can't load Texture ({}): {}", _ID, SDL_GetError());
		return false;
	}
	SPDLOG_INFO ("Load Texture ({}) successfull", _ID);
	return true;
}

void cPicture::draw ( void )
{
	SDL_RenderCopy ( _parent->getRenderer(), _texture, NULL, NULL );
}

SDL_Renderer* cPicture::getRenderer ( void )
{
	_parent->getRenderer ();
}

cRect cPicture::getMySize ( void )
{
	SPDLOG_DEBUG ("_getMySize not avlaible");
	cRect r;
	return r;
	//only avlaible if a widget can have a child
}

}
