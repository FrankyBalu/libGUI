/*
 * log.cpp
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


#include "../include/log.h"
#include <SDL.h>

namespace LIBGUI {
Log *Log::instance = 0;

Log *Log::LogInst()
{
    if (instance == 0)
    {
        instance = new Log();
    }

    return instance;
}

Log::Log()
{
	_priority = LOG_PRIORITY_VERBOSE;
	_category = LOG_CATEGORY_APP;
}


void Log::setPriority ( LogPriority pri )
{
	SDL_LogSetPriority(30,(SDL_LogPriority)pri);
}

void Log::setCategory ( int category )
{
	_category = category;
}


void Log::INFO ( PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( _category, (SDL_LogPriority)LOG_PRIORITY_INFO, msg, ap );
	va_end (ap);
}

void Log::DEBUG ( PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( _category, (SDL_LogPriority)LOG_PRIORITY_DEBUG, msg, ap );
	va_end (ap);
}

void Log::WARN ( PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( _category, (SDL_LogPriority)LOG_PRIORITY_WARN, msg, ap );
	va_end (ap);
}

void Log::ERROR ( PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( _category, (SDL_LogPriority)LOG_PRIORITY_ERROR, msg, ap );
	va_end (ap);
}


void Log::VERBOSE ( PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( _category, (SDL_LogPriority)LOG_PRIORITY_VERBOSE, msg, ap );
	va_end (ap);
}

void Log::INFO (int cat, PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( cat, (SDL_LogPriority)LOG_PRIORITY_INFO, msg, ap );
	va_end (ap);
}

void Log::DEBUG (int cat, PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( cat, (SDL_LogPriority)LOG_PRIORITY_DEBUG, msg, ap );
	va_end (ap);
}

void Log::WARN (int cat, PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( cat, (SDL_LogPriority)LOG_PRIORITY_WARN, msg, ap );
	va_end (ap);
}

void Log::ERROR (int cat, PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( cat, (SDL_LogPriority)LOG_PRIORITY_ERROR, msg, ap );
	va_end (ap);
}


void Log::VERBOSE ( int cat, PRINTF_FORMAT_STRING const char *msg, ... )
{
	va_list ap;
	va_start(ap, msg);
	SDL_LogMessageV ( cat, (SDL_LogPriority)LOG_PRIORITY_VERBOSE, msg, ap );
	va_end (ap);
}
}//namespace LIBGUI
