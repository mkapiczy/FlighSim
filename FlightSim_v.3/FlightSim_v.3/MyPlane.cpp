/**
* \file MyPlane.cpp
* \brief Plik Ÿród³owy klasy MyPlane
*/

#include "stdafx.h"
#include "MyPlane.h"
#include "Airport.h"

MyPlane::State MyPlane::state = MyPlane::ASCENDING;

MyPlane::MyPlane()
{
}

MyPlane::MyPlane(int id, sf::Vector2f position)
{
	next = NULL;
	this->id = id;
	this->position.x = position.x;
	this->position.y = position.y;
	this->rotation = 0;
}

MyPlane::~MyPlane()
{
}

void MyPlane::move(double dt)
{
	/// Zmienna skaluj¹ca prêdkoœæ
	double vscale = 100;
	height = abs(position.y - 2160)*7.5;

	/// Obliczenie prêdkoœci wzglêdem wiatru
	if (windDirection >= -90 && windDirection <= 90)
	{
		v = (velocity - windSpeed) * 1000 / 3600;
	}

	else if ((windDirection >= -180 && windDirection < -90) || (windDirection <= 180 && windDirection>90))
	{
		v = (velocity + windSpeed) * 1000 / 3600;
	}

	/// Wyliczenie wartoœci si³
	gravity = 9.81;
	Pz = 0.5*Cz*S*ro*v*v;
	Fg = mass*gravity;

	/// Wyliczenie wartoœci prêdkoœci w osi y
	speed.y += (Pz - Fg)*dt / mass;

	/// Podejscie do l¹dowania, gdy stan paliwa spadnie poni¿ej alarmowego
	if (fuel < 35000 && fuelalarm == false)
	{
		cout << "\r" << "Malo paliwa! Podchodze do ladowania!";
		state = State::DESCENDING;
		fuelalarm = true;
	}

	/// Logika, w przypadku wznoszenia
	if (state == State::ASCENDING)
	{
		if (rotation > -10) rotation -= 0.05;

		if (Pz < Fg)
		{
			accelerate(1);
		}
		if (Pz >= Fg && velocity < 900 && position.y>800)
		{
			accelerate(0.25);
		}

		if (position.y <= 800)
		{
			state = State::MAINTAINING;
		}
		else
		{
			position.x += velocity*cos((rotation * 3.14) / 180.0f)*dt;
			position.y += speed.y*sin((rotation * 3.14) / 180.0f)*dt;
		}
	}

	/// Logika w przypadku schodzenia
	if (state == State::DESCENDING)
	{
		/// Wytraca prêdkoœæ
		if (Pz > 5 * Fg)
		{
			decelerate(0.25);
			if (rotation < 1) rotation += 0.05;
			if (rotation > 1) rotation -= 0.05;
		}
		/// Podchodzi do l¹dowania
		if (Pz <= 5 * Fg)
		{
			if (rotation < 3) rotation += 0.05;
			if (rotation > 3) rotation -= 0.05;

			if (velocity > 400) decelerate(0.25);
		}

		if (position.y > 1700)
		{
			state = State::MAINTAINING;
			fuelalarm = false;
		}

		position.x += velocity*cos((rotation * 3.14) / 180.0f)*dt;
		position.y += speed.y*sin((rotation * 3.14) / 180.0f)*dt;
	}

	/// Logika w przypadku lotu na sta³ej wysokoœci
	if (state == State::MAINTAINING)
	{
		if (fuel < 35000 && fuelalarm == true)
		{
			cout << "\r" << "Malo paliwa! Podchodze do ladowania!";
			state = State::DESCENDING;
		}

		if (rotation < 0) rotation += 0.05;
		if (rotation > 0) rotation -= 0.05;


		if (position.y >= 1700) state = State::LANDING;

		position.x += velocity*cos((rotation * 3.14) / 180.0f)*dt;
		position.y += speed.y*sin((rotation * 3.14) / 180.0f)*dt;
	}

	if (position.y < 600) position.y = 600;

	if (position.y > 2100)
	{
		position.y = 2100;
	}

	if (position.x >= 1920)
		position.x = 640;

	if (position.x < 640)
		position.x = 1920;

	distance += velocity / 10 * dt;
}

void MyPlane::consumefuel()
{
	if (fuel > 0) fuel = (50000 - (distance * 5));
	else printf("\nBrak paliwa!\n");
}