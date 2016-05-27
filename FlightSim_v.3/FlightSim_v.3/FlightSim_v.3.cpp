/**
* \mainpage
* \par FlightSim
* Program symuluj�cy dzia�anie lotniska oraz symulacj� lotu samolotu.
* \author Micha� Kapiczy�ski
* \date 2015.06.11
* \version 1.0
* \par Kontakt:
* \a mix.kap@gmail.com
*/

#include "stdafx.h"
#include "Simulation.h"

using namespace std;
using namespace sf;


int main()
{
	Simulation simulation;
	simulation.runSim();

	return EXIT_SUCCESS;
}
