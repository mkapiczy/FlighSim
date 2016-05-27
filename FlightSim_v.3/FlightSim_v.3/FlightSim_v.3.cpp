/**
* \mainpage
* \par FlightSim
* Program symuluj¹cy dzia³anie lotniska oraz symulacjê lotu samolotu.
* \author Micha³ Kapiczyñski
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
