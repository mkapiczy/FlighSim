/**
* \file MyPlane.h
* \brief Plik nag³ówkowy klasy MyPlane
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
	/// Konstruktor domyœlny
	MyPlane();
	/// Konstruktor 
	MyPlane(int id, sf::Vector2f position);
	/// Destruktor
	~MyPlane();
	/** \brief Logika ruchu samolotu
	*
	* Funkcja odpowiad¹jaca za logikê poruszania sie samolotu w czasie lotu
	*/
	void move(double dt);
	/** \brief Spalanie paliwa
	*
	* Funkcja odpowiad¹jaca za aktualizacje stanu paliwa
	*/
	void consumefuel();
	/// Wielkosc samolotu
	sf::Vector2f size = { 256, 84 };

	/// Typ wyliczeniowy reprezentuj¹cy stan samolotu
	typedef enum State{
		ASCENDING,
		MAINTAINING,
		DESCENDING,
		TOLANDING,
		LANDING,
		COUNT
	};
	/**
	* Zmienna typu State, przechowuj¹ca aktualny stan samolotu
	* \see State
	*/
	static State state;
	/// Predkoœæ samolotu
	sf::Vector2f speed = { 100, 100 };
	/// Przebyty dystans
	double distance=0;
	/// Wysokosc, na jaka wznosi sie samolot
	double height = abs(position.y - 2160)*7.5;
	/// Prêdkoœæ wzglêdem wiatru =  velocity - wind->speed;
	double v = 0; 
	/// Pojemnosc baku - 50 ton
	double fuel=50000; 


private:
	/// Masa samolotu [kg]
	const double mass = 300000; 
	/// Wspolczynnik si³y noœnej
	const double Cz = 1.4; 
	/// Powierzchnia noœna [m^2]
	const double S = 550; 
	/// Gêstoœæ powietrza [kg/m^3]
	const double ro = 1.2; 

	/// Si³a ciê¿koœci
	double Fg = mass*gravity;
	/// Si³a noœna
	double Pz = 0.5*Cz*S*ro*v*v;
};

