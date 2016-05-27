/**
* \file Bus.h
* \brief Plik nag³ówkowy klasy Bus
*/

#pragma once
#include "Vehicle.h"

/** \brief Klasa reprezentujaca Autobus
*
* Definicja klasy Bus
*/

class Bus : public Vehicle
{
public:
	/// Konstruktor domyœlny
	Bus();
	/// Konstruktor
	Bus(int initid, sf::Vector2f position);
	/// Destruktor
	~Bus();
	/** \brief Logika ruchu autobusu
	*
	* Funkcja odpowiad¹jaca za logikê poruszania sie autobusu po lotnisku
	*/
	void move();

	/// WskaŸnik na kolejny element listy jednokierunkowej elementow Bus
	Bus *next;

	/// Typ wyliczeniowy okreslajacy stan obiektu klasy Bus
	typedef enum BusState{
		BUSTOLANDING,
		BUSTODEPARTING,
		BUSFROMLANDING,
		BUSFROMDEPARTING
	};
	/// Zmienna typu BusState reprezentujaca aktualny stan obiektu klasy Bus
	BusState state;

};

