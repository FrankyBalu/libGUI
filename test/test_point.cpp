/*
 * test_point.cpp
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

#include <iostream>
#include "../include/log.h"
#include "../include/point.h"

int RETURN_CODE = 0;

int main ()
{
	LOG->setPriority ( LIBGUI::LOG_PRIORITY_INFO );
	LOG->INFO ("\t\tTeste Klasse Point\n\n");
	
	LOG->DEBUG ("Lege Point Punkt1 an\n");
	LIBGUI::Point Punkt1;
	LOG->DEBUG ("Lege Point Punkt2(2,5) an\n");
	LIBGUI::Point Punkt2(2,5);

	LOG->DEBUG ("\n\tPrüfe ob Werte stimmen\n");
	//Punkt 1
	if ( (Punkt1.GetX()==0) && (Punkt1.GetY() == 0) )
	{
		LOG->DEBUG ("Punkt1 stimmt\n");
	}
	else
	{
		if ( Punkt1.GetX() != 0 )
			LOG->ERROR ("Punkt1.x stimmt nicht!\n");
		if ( Punkt1.GetY() != 0 )
			LOG->ERROR ("Punkt1.y stimmt nicht!\n");
		RETURN_CODE = -1;
	}
	//Punkt 2
	if ( (Punkt2.GetX() == 2) && (Punkt2.GetY() == 5) )
	{
		LOG->DEBUG ("Punkt2 stimmt");
	}
	else
	{
		if ( Punkt2.GetX() != 2 )
			LOG->ERROR ("Punkt2.x stimmt nicht!\n");
		if ( Punkt1.GetY() != 5 )
			LOG->ERROR ("Punkt2.y stimmt nicht!\n");
		RETURN_CODE = -1;
	}
	
	LOG->DEBUG ("\n\tKopiere Punkt2 in Punkt1 und Prüfe das Ergebnis\n");
	LOG->DEBUG ("\t\tvorher und nachher\n");
	
	if ( Punkt1 == Punkt2 )
	{
		LOG->ERROR ("Punkt1 und Punkt2 sind vor dem kopieren gleich!\n");
		RETURN_CODE = -1;
	}
	Punkt1 = Punkt2;
	if ( Punkt1 == Punkt2 )
		LOG->DEBUG ("Punkt1 und Punkt2 sind nach dem kopieren gleich\n");
	else
	{
		LOG->ERROR ("Punkt1 und Punkt2 nach dem Kopieren nicht glich!\n");
		RETURN_CODE = -1;
	}
	if ( RETURN_CODE == 0 )
		LOG->INFO ("Alle Tests bestanden\n");
	else
		LOG->ERROR ("Ein oder mehrere Tests nicht bestanden!\n");
	return RETURN_CODE;	
}
