/**
* \file Vehicle.h
* \brief Plik nag³ówkowy klasy Vehicle
*/

#pragma once
#include "Wind.h"

/** \brief Abstrakcyjna klasa reprezentuj¹ca pojazd
*
* Definicja klasy Vehicle
*/

class Vehicle
{
public:
	Vehicle();
	~Vehicle();
	/// Pozycja pojazdu
	sf::Vector2f position;
	/// Prêdkoœæ
	double velocity = 0;
	/// Obrót
	double rotation = 0; 
	/// Skala do rysowania
	double scale; 
	/// Czujnik kierunku wiatru
	double windDirection = 0;
	/// Czujnik prêdkoœci wiatru
	double windSpeed = 0; 
	/// Id pojazdu
	int id; 
	/// Przyœpieszenie ziemskie
	double gravity = 9.81;
	/// Zmienna odpowiadajaca za sygnalizacje niskiego stanu paliwa
	bool fuelalarm = false;
	/** \brief Przyœpiesz
	*
	* Funkcja odpowiada za wzrost prêdkoœci pojazdu
	*/
	void accelerate(double dv);
	/** \brief PZwolnij
	*
	* Funkcja odpowiada za spadek prêdkoœci pojazdu
	*/
	void decelerate(double dv);
	/** \brief Czysto wirtualna funkcja ruchu pojazdu
	*
	*/
	virtual void move() = 0;

	


private:
	/// WskaŸnik na obiekt klasy Wind
	//Wind *wind;
	/// Stan paliwa
	double fuel;
	
};

