/**
* \file Wind.cpp
* \brief Plik Ÿród³owy klasy Wind
*/

#include "stdafx.h"
#include "Wind.h"

double Wind::speed = 0;
double Wind::direction = 0;

Wind::Wind()
{
}


Wind::~Wind()
{
}

double Wind::windspeed()
{
	speed = (rand() % (70 - 0 + 1)) + 0;

	return speed;
}

double Wind::winddirection()
{
	direction = (rand() % (180 - (-180) + 1)) - 180;

	return direction;
}
void Wind::randomWindChange()
{
	Wind::direction = winddirection();
	Wind::speed = windspeed();
}
