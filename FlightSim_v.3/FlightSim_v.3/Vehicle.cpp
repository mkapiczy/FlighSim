/**
* \file Vehicle.cpp
* \brief Plik Ÿród³owy klasy Vehicle
*/

#include "stdafx.h"
#include "Vehicle.h"
#include "Airport.h"


Vehicle::Vehicle()
{
}


Vehicle::~Vehicle()
{
}


void Vehicle::accelerate(double dv)
{
	velocity += dv;
}

void Vehicle::decelerate(double dv)
{
	velocity -= dv;
}
