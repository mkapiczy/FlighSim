/**
* \file Simulation.h
* \brief Plik nag≥Ûwkowy klasy Simulation
*/


#pragma once
#include "Engine.h"
#include "GraphicEngine.h"

/** \brief Klasa odpowiedzialna za zarzπdzanie stanami symulacji
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
	/// Moøliwe stany symulacji
	typedef enum SimState{MENU,
	AIRPORT,
	FLIGHT,
	END,
	COUNT};

	/// Zmienna typu SimState przechowujπca stan symulacji
	static SimState simState;
	/** \brief Start symulacji
	*
	* Funkcja rozpoczynajπca dzia≥ania symulacji
	*/
	void runSim();

private:
	/// Wskaünik na obiekt klasy Engine
	Engine *engine;
};

