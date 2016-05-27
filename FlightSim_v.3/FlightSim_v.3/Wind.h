/**
* \file Wind.h
* \brief Plik nag��wkowy klasy Wind
*/
#pragma once

/** \brief Klasa reprezentuj�ca wiatr
*
* Definicja klasy Wind
*/

class Wind
{
public:
	/// Konstruktor
	Wind();
	/// Destruktor
	~Wind();
	/** \brief Losowa zmiana pr�dko��i i kierunku wiatru
	*
	* Funkcja odpowiada za losow� zmian� pr�dkosci i kierunku wiatru
	* oraz przypisanie tych warto�ci do zmiennych spped i direction
	*/
	void randomWindChange();
	/** \brief Losowa zmiana pr�dko�ci
	*
	* Funkcja odpowiada za losow� zmian� pr�dkosci wiatru
	*/
	double windspeed();
	/** \brief Losowa zmiana kierunku
	*
	* Funkcja odpowiada za losow� zmian� kierunku wiatru
	*/
	double winddirection();
	
	/// Zmienna statyczna reprezentuj�ca pr�dko�� wiatru
	static double speed;
	/// Zmienna statyczna reprezentuj�ca kierunek wiatru
	static double direction;
};

