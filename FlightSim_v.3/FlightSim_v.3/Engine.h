/**
* \file Engine.h
* \brief Plik nag�owkowy klasy Engine
*/

#pragma once

#include "GraphicEngine.h"
#include "Wind.h"
#include "Plane.h"
#include "MyPlane.h"
#include "Bus.h"

/** \brief Klasa reprezentujaca silnik programu
*
* Definicja klasy Engine
*/

class Engine
{
public:
	/// Konstruktor
	Engine();
	/// Destruktor
	~Engine();
	/** \brief Logika symulacji menu
	*
	* Funkcja odpowiadajaca za dzialanie menu
	*/
	void menu();
	/** \brief Logika symulacji lotniska
	*
	* Funkcja odpowiadajaca za dzialanie symulacji lotniska
	*/
	void airport();
	/** \brief Logika symulacji lotu
	*
	* Funkcja odpowiadaj�ca za dzia�anie symulacji lotu
	*/
	void flight();


private:
	/// Wska�nik na obiekt klasy GraphicEngine
	GraphicEngine *gengine;
	/// Wska�nik na obiekt klasy Wind
	Wind *wind;
	/// Wska�nik na obiekt klasy Plane
	Plane *plane;
	/// Wska�nik na obiekt klasy MyPlane
	MyPlane *myplane;
	/// Wska�nik na obiekt klasy Bus
	Bus *bus;
	/// Listy jednokierunkowe
	/// Kolejka do l�dowania
	Airport tolanding;
	/// Kolejka do startu
	Airport todeparting;
	/// Kolejka na lotnisku - "w hangarze"
	Airport atairport;
	/// Kolejka na pasie wylotowym
	Airport departing;
	/// Kolejka na pasie do l�dowania
	Airport landing;
	/// Kolejka autobus�w do wjazdu w obszar ladowania
	Airport buslandingqueue;
	/// Kolejka autobusow do wjazdu w obszar wylotow
	Airport busdepartingqueue;
	/// Kolejka autobusow znajdujacych sie w obszarze ladowania
	Airport busatlanding;
	/// Kolejka autobusow znajdujacych sie w obszarze wylotow
	Airport busatdeparting;
};

