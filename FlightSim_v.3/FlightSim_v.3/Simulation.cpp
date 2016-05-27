/**
* \file Simulation.cpp
* \brief Plik �r�d�owy klasy Simulation
*/

#include "stdafx.h"
#include "Simulation.h"
#include "Engine.h"

Simulation::SimState Simulation::simState=AIRPORT;

Simulation::Simulation()
{
	simState = SimState::MENU;
	engine = new Engine();
}


Simulation::~Simulation()
{
	delete engine;
}

void Simulation::runSim()
{
	/// flaga symulacji
	bool simulation = true;

	/// g��wna p�tla symulacji
	while (simulation)
	{ 
		switch (simState)
		{
		case SimState::MENU:
		{
			engine->menu();
			break;
		}
		case SimState::AIRPORT:
		{
			engine->airport();
			break;
		}
		case SimState::FLIGHT:
		{
			engine->flight();
			break;
		}
		case SimState::END:
		{
			simulation = false;
			break;
		}
		}
	}
}
