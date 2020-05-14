/*
 * log.h
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


#ifndef __LIBGUI_LOG__
#define __LIBGUI_LOG__


#include <string>
#define LOG LIBGUI::Log::LogInst()

namespace LIBGUI {

enum LOG_CATEGORY {
    LOG_CATEGORY_LIBGUI = 30,
    LOG_CATEGORY_APP,
};

typedef enum
{
    LOG_PRIORITY_VERBOSE = 1,
    LOG_PRIORITY_DEBUG,
    LOG_PRIORITY_INFO,
    LOG_PRIORITY_WARN,
    LOG_PRIORITY_ERROR,
    LOG_PRIORITY_CRITICAL,
    NUM_LOG_PRIORITIES
} LogPriority;

#define PRINTF_FORMAT_STRING
#define PRINTF_VARARG_FUNC( fmtargnumber ) __attribute__ (( format( __printf__, fmtargnumber, fmtargnumber+1 )))


class Log
{
    private:
        static Log *instance;
		Log();
		LogPriority _priority;
		int _category;

    public:
        static Log *LogInst();
        
        void setPriority ( LogPriority pri );
        void setCategory ( int category );
        
        void VERBOSE ( PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(2); 
        void INFO ( PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(2);
        void DEBUG ( PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(2);
        void WARN ( PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(2);
        void ERROR ( PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(2);
        
        void VERBOSE (int cat, PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(3); 
        void INFO (int cat, PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(3);
        void DEBUG (int cat, PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(3);
        void WARN (int cat,  PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(3);
        void ERROR (int cat, PRINTF_FORMAT_STRING const char *msg, ... )PRINTF_VARARG_FUNC(3);
};




}//namespace LIBGUI

#endif //__LIBGUI_LOG__
