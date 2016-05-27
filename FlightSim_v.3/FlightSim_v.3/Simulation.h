/**
* \file Simulation.h
* \brief Plik nag��wkowy klasy Simulation
*/


#pragma once
#include "Engine.h"
#include "GraphicEngine.h"

/** \brief Klasa odpowiedzialna za zarz�dzanie stanami symulacji
*
* Definicja klasy Simulation
*/

class Simulation
{
public:
	/// Konstruktor
	Simulation();
	/// Desktruktor
	~Simulation();
	/// Mo�liwe stany symulacji
	typedef enum SimState{MENU,
	AIRPORT,
	FLIGHT,
	END,
	COUNT};

	/// Zmienna typu SimState przechowuj�ca stan symulacji
	static SimState simState;
	/** \brief Start symulacji
	*
	* Funkcja rozpoczynaj�ca dzia�ania symulacji
	*/
	void runSim();

private:
	/// Wska�nik na obiekt klasy Engine
	Engine *engine;
};

