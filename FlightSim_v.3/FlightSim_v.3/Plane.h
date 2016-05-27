/**
* \file Plane.h
* \brief Plik nag��wkowy klasy Plane
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
	/// Konstruktor domy�lny
	Plane();
	/// Konstruktor
	Plane(int initid, sf::Vector2f position);
	/** \brief Logika ruchu samolotu na lotnisku
	*
	* Funkcja odpowiad�jaca za logik� poruszania sie samolotu na lotnisku
	*/
	void move();

	/// Typ wyliczeniowy reprezentuj�cy stan samolotu
	typedef enum PlaneState{
		LANDING,
		DEPARTING,
		PARKED,
		REFUSED,
		COUNT
	};
	/**
	* Zmienna typu State, przechowuj�ca aktualny stan samolotu
	* \see PlaneState
	*/
	PlaneState state;

	/// Wska�nik na kolejny element listy jednokierunkowej element�w Plane
	Plane* next;
};

