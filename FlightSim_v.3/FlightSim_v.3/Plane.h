/**
* \file Plane.h
* \brief Plik nag³ówkowy klasy Plane
*/
#pragma once
#include "Wind.h"
#include "Vehicle.h"


/** \brief Klasa reprezentujaca obiekt samolotu na lotnisku
*
* Definicja klasy Plane
*/

class Plane : public Vehicle
{
public:
	/// Konstruktor domyœlny
	Plane();
	/// Konstruktor
	Plane(int initid, sf::Vector2f position);
	/** \brief Logika ruchu samolotu na lotnisku
	*
	* Funkcja odpowiad¹jaca za logikê poruszania sie samolotu na lotnisku
	*/
	void move();

	/// Typ wyliczeniowy reprezentuj¹cy stan samolotu
	typedef enum PlaneState{
		LANDING,
		DEPARTING,
		PARKED,
		REFUSED,
		COUNT
	};
	/**
	* Zmienna typu State, przechowuj¹ca aktualny stan samolotu
	* \see PlaneState
	*/
	PlaneState state;

	/// WskaŸnik na kolejny element listy jednokierunkowej elementów Plane
	Plane* next;
};

