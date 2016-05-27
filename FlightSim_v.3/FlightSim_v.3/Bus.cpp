/**
* \file	Bus.cpp
* \brief Plik Ÿród³owy klasy Bus
*/


#include "stdafx.h"
#include "Bus.h"
#include "Airport.h"


Bus::Bus()
{
}

Bus::Bus(int initid, sf::Vector2f position)
{
	id = initid;
	next = NULL;
	this->position.x = position.x;
	this->position.y = position.y;
}

Bus::~Bus()
{
}

void Bus::move()
{
	/// Instancja klasy Airport
	Airport airport;
	/// Zmienna pomocnicza do skalowania prêdkoœci
	int vscale = 100;

	velocity = 50;

	/// Logika ruchu autobusu w kierunku "hangaru" po pasie do ladowania
	if (state == BusState::BUSTOLANDING)
	{
		if (position.y > 500)
		{
			
		}
		if (position.y <= 500 && position.y > 380)
		{
			if ((rotation-90)<-15) rotation += 0.5;
		}
		if (position.y <= 380)
		{
			if ((rotation - 90) < 0) rotation += 0.5;
		}

		position.x += (velocity / vscale)*cos(((rotation - 90) * 3.14) / 180.0f);
		position.y += (velocity / vscale)*sin(((rotation - 90)* 3.14) / 180.0f);
	}

	/// Logika ruchu autobusu od "hangaru" po pasie do ladowania
	if (state == BusState::BUSFROMLANDING)
	{

		if (position.x == airport.hangarposition.x)
		{
			if (rotation == 0) rotation = -90;
		}

		if (position.x > 200)
		{

		}
		if (position.x <= 200 && position.x > 120)
		{
			if ((rotation)>-165) rotation -= 0.5;
		}
		if (position.x <=120 && position.x >= 80)
		{
			if ((rotation) > -180) rotation -= 0.5;
		}
		position.x += (velocity / vscale)*cos(((rotation - 90) * 3.14) / 180.0f);
		position.y += (velocity / vscale)*sin(((rotation - 90)* 3.14) / 180.0f);
	}

	/// Logika ruchu autobusu w kierunku hangary po pasie do wylotow
	if (state == BusState::BUSTODEPARTING)
	{
		
		if (position.x <= 640 && position.y <= 550 && position.y > 400)
		{
			if ((rotation - 90)< 0) rotation += 0.5;
		}
		if (position.x <=640 && rotation >= 90 && position.x<800)
		{
			if (position.y < 550) rotation += 0.25;
			if (position.y >= 550 && rotation > 90) rotation -= 0.5;
		}
		if (position.x >= 800 && position.y>=380)
		{
			if (rotation > -45) rotation -= 0.5;
		}
		if (position.x >= 640 && position.y <380)
		{
			if (rotation > -90) rotation -= 0.5;
		}
		position.x += (velocity / vscale)*cos(((rotation - 90) * 3.14) / 180.0f);
		position.y += (velocity / vscale)*sin(((rotation - 90)* 3.14) / 180.0f);
	}

}