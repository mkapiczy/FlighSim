/**
* \file MyPlane.h
* \brief Plik nag��wkowy klasy MyPlane
*/

#pragma once
#include "Plane.h"

/** \brief Klasa reprezentujaca obiekt samolotu podczas symulacji lotu
*
* Definicja klasy MyPlane
*/

class MyPlane : public Plane
{
public:
	/// Konstruktor domy�lny
	MyPlane();
	/// Konstruktor 
	MyPlane(int id, sf::Vector2f position);
	/// Destruktor
	~MyPlane();
	/** \brief Logika ruchu samolotu
	*
	* Funkcja odpowiad�jaca za logik� poruszania sie samolotu w czasie lotu
	*/
	void move(double dt);
	/** \brief Spalanie paliwa
	*
	* Funkcja odpowiad�jaca za aktualizacje stanu paliwa
	*/
	void consumefuel();
	/// Wielkosc samolotu
	sf::Vector2f size = { 256, 84 };

	/// Typ wyliczeniowy reprezentuj�cy stan samolotu
	typedef enum State{
		ASCENDING,
		MAINTAINING,
		DESCENDING,
		TOLANDING,
		LANDING,
		COUNT
	};
	/**
	* Zmienna typu State, przechowuj�ca aktualny stan samolotu
	* \see State
	*/
	static State state;
	/// Predko�� samolotu
	sf::Vector2f speed = { 100, 100 };
	/// Przebyty dystans
	double distance=0;
	/// Wysokosc, na jaka wznosi sie samolot
	double height = abs(position.y - 2160)*7.5;
	/// Pr�dko�� wzgl�dem wiatru =  velocity - wind->speed;
	double v = 0; 
	/// Pojemnosc baku - 50 ton
	double fuel=50000; 


private:
	/// Masa samolotu [kg]
	const double mass = 300000; 
	/// Wspolczynnik si�y no�nej
	const double Cz = 1.4; 
	/// Powierzchnia no�na [m^2]
	const double S = 550; 
	/// G�sto�� powietrza [kg/m^3]
	const double ro = 1.2; 

	/// Si�a ci�ko�ci
	double Fg = mass*gravity;
	/// Si�a no�na
	double Pz = 0.5*Cz*S*ro*v*v;
};

