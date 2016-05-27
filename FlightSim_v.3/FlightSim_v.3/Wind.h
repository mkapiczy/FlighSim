/**
* \file Wind.h
* \brief Plik nag³ówkowy klasy Wind
*/
#pragma once

/** \brief Klasa reprezentuj¹ca wiatr
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
	/** \brief Losowa zmiana prêdkoœæi i kierunku wiatru
	*
	* Funkcja odpowiada za losow¹ zmianê prêdkosci i kierunku wiatru
	* oraz przypisanie tych wartoœci do zmiennych spped i direction
	*/
	void randomWindChange();
	/** \brief Losowa zmiana prêdkoœci
	*
	* Funkcja odpowiada za losow¹ zmianê prêdkosci wiatru
	*/
	double windspeed();
	/** \brief Losowa zmiana kierunku
	*
	* Funkcja odpowiada za losow¹ zmianê kierunku wiatru
	*/
	double winddirection();
	
	/// Zmienna statyczna reprezentuj¹ca prêdkoœæ wiatru
	static double speed;
	/// Zmienna statyczna reprezentuj¹ca kierunek wiatru
	static double direction;
};

