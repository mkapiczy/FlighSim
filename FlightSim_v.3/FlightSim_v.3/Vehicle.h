/**
* \file Vehicle.h
* \brief Plik nag��wkowy klasy Vehicle
*/

#pragma once
#include "Wind.h"

/** \brief Abstrakcyjna klasa reprezentuj�ca pojazd
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
	/// Pr�dko��
	double velocity = 0;
	/// Obr�t
	double rotation = 0; 
	/// Skala do rysowania
	double scale; 
	/// Czujnik kierunku wiatru
	double windDirection = 0;
	/// Czujnik pr�dko�ci wiatru
	double windSpeed = 0; 
	/// Id pojazdu
	int id; 
	/// Przy�pieszenie ziemskie
	double gravity = 9.81;
	/// Zmienna odpowiadajaca za sygnalizacje niskiego stanu paliwa
	bool fuelalarm = false;
	/** \brief Przy�piesz
	*
	* Funkcja odpowiada za wzrost pr�dko�ci pojazdu
	*/
	void accelerate(double dv);
	/** \brief PZwolnij
	*
	* Funkcja odpowiada za spadek pr�dko�ci pojazdu
	*/
	void decelerate(double dv);
	/** \brief Czysto wirtualna funkcja ruchu pojazdu
	*
	*/
	virtual void move() = 0;

	


private:
	/// Wska�nik na obiekt klasy Wind
	//Wind *wind;
	/// Stan paliwa
	double fuel;
	
};

