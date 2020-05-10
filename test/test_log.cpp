#include "../include/log.h"
#include <string>

int main ()
{
	int i = 30;
	std::string h ("test"); 
	LOG->setPriority ( LIBGUI::LOG_PRIORITY_VERBOSE );
	LOG->VERBOSE ("das ist ein VERBOSE log");
	LOG->DEBUG ("das sind %d tests", i);
	LOG->INFO ("Das ist ein Info log %s", h.c_str());
	LOG->WARN ("Das ist ein Warn log");
	LOG->ERROR ("Das ist ein ERROR log");
}
