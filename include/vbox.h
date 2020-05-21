/*
 * vbox.h
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


#ifndef __LIBGUI_VBOX__
#define __LIBGUI_VBOX__

#include "widget.h"
#include <string>
#include "rect.h"
#include "video.h"
#include "renderer.h"
#include "event.h"
#include <map>
#include <vector>

namespace LIBGUI {


class VBox : public Widget {
protected:
	std::map<std::string,Widget*>   _Child;      /**<Alle Childs in alphabetischer Reihenfolge*/
	std::vector<std::string>        _ChildOrder; /**<Die Reihenfolge der Widgets*/
	std::map<std::string,bool>		_ChildIsFixed; /**<Child hat feste höhe*/
	int     _ChildCount;			/**<Anzahl der Childs ohne feste höhe*/
	int 	_FixedSizeChildCount;	/**<Anzahl der Childs mit fester höhe*/
	int     _FixedWidth;	/**<Hat die VBox eine feste Breite*/
	int     _FixedHeight;  /**<Hat die VBox eine feste Höhe*/
	int 	_FixedHeightAll; /**<insgesamt höhe aller fixed size Widgets*/
	
	/**
	 * \brief Initialisiert die VBox, wird vom Constructor aufgerufen
	 *
	 * \param parent 	Elern Widget der VBox
	 * \param ID		Eindeutiger name der VBox
	 * \param width		Feste Breite für die VBox oder -1, für dynamische Breite
	 * \param height	Feste Höhe für die VBox oder -1 für dynamische Höhe
	 */
	void		Init			( Widget *parent, std::string ID, int width, int height );

	
public:

	/**
	 * \brief Konstruktor von VBox dynamische größe
	 *			Erstellt eine VBox mit dynamischer größe, die sich der des Eltern 
	 *			Widgets anpasst
	 *
	 * \param parent 	Elern Widget der VBox
	 * \param ID		Eindeutiger name der VBox
	 */
	            VBox            ( Widget *parent, std::string ID );
	 
	 /**
	 * \brief Konstruktor von VBox fester größe
	 *			Erstellt eine VBox mit fester größe, die sich nicht an das 
	 *			Eltern Widgets anpasst
	 *
	 * \param parent 	Elern Widget der VBox
	 * \param ID		Eindeutiger name der VBox
	 * \param width		Feste Breite für die VBox oder -1, für dynamische Breite
	 * \param height	Feste Höhe für die VBox oder -1 für dynamische Höhe
	 */
	            VBox			( Widget *parent, std::string ID, int width, int height );
	
	/**
	 * \brief Gibt den genutzten Renderer zurück
	 */
	Renderer*   GetRenderer     ( void );
	
	/**
	 * \brief Gibt die Größe der VBox zurück
	 */
	Rect	    GetSize	        ( void );
	
	/**
	 * \brief Fügt ein Widget mit dynamischer größe hinzu
	 *
	 * \param child Das Widget das hinzugefügt werden soll
	 * \param ID ID des Widgets das hinzugefügt werden soll, diese ID darf noch
	 * 			 im Widget vergeben sein
	 */
	bool	    AddChild	    ( Widget *child, std::string ID );
	
	/**
	 * \brief Fügt ein Widget mit fester größe hinzu
	 *
	 * \param child Das Widget das hinzugefügt werden soll
	 * \param ID ID des Widgets das hinzugefügt werden soll, diese ID darf noch
	 * 			 im Widget vergeben sein
	 * \param width	Die Breite des hinzu zu fügenden Widgets oder -1 für dynamisch
	 * \param height Die Höhe des hinzu zu fügenden Widgets oder -1 für dynamisch
	 */
	bool	    AddChild	    ( Widget *child, std::string ID, int width, int height );

	/**
	 * \brief Funktion aus der Widget-Klasse, die Implementiert werden muss,
	 *        Wenn sie nicht wirklich gebraucht wird, vielleicht aus Widget entfernen
	 *		  und nur in den Klassen inplementieren, in denen es gebraucht wird
	 */
	bool        ChangeChild     ( std::string ID );
	
	/**
	 * \brief Größe der VBox soll geändert werden
	 *
	 * \praram rect Die neue größe die die VBox annehmen soll.
	 * 			Wenn die VBox eine Feste Größe hat oder ein parameter kleiner 0
	 *			ist, wird die angabe ignoriert.
	 */
	void	    ChangeSize	    ( Rect rect );
	
	/**
	 * \brief Zur behandlung von events, wird nur bei sichtbaren Widgets ausgeführt
	 *
	 * \param event Das event, das vom parent durchgereicht wird
	 */
	void	    ProcessEvent	( Event *event );
	
	/**
	 * \brief Last das Widget (und die childs) Rendern, nur wenn sichtbaren
	 */
	bool	    Draw	        (void );
	
	/**
	 * \breif Wird bei jedem durchlauf der Program schleife ausgeführt, unabhängig
	 *		  davon ob das Widget sichtbar ist oder nicht
	 */
	void        Update          ( void );
	
	/**
	 * \brief Ändert das Offset des Widgets, werte unter 0 werden ignoriert
	 *
	 * \param offset Das neue Offset des Widgets
	 */
	void	    ChangeOffset    ( Point offset );
	
	/**
	 * \brief Gibt das aktuelle Offset zurück
	 */
	Point	    GetOffset	    ( void );
	bool		IsFixedH		( void ){}
	bool		IsFixedW		( void ){}
	std::string GetID			( void );

	void ( *onClick )	( void *data );
	void ( *onPress )	( void *data );
	void ( *onSlideH )	( void *data );
	void ( *onSlideV )	( void *data );
	void ( *onRelease )	( void *data );
	
};


}//namespace LIBGUI

#endif //__LIBGUI_VBOX__
