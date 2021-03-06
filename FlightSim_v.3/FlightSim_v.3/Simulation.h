/**
* \file Simulation.h
* \brief Plik nagłówkowy klasy Simulation
*/


#pragma once
#include "Engine.h"
#include "GraphicEngine.h"

/** \brief Klasa odpowiedzialna za zarządzanie stanami symulacji
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
	/// Możliwe stany symulacji
	typedef enum SimState{MENU,
	AIRPORT,
	FLIGHT,
	END,
	COUNT};

	/// Zmienna typu SimState przechowująca stan symulacji
	static SimState simState;
	/** \brief Start symulacji
	*
	* Funkcja rozpoczynająca działania symulacji
	*/
	void runSim();

private:
	/// Wskaźnik na obiekt klasy Engine
	Engine *engine;
};

