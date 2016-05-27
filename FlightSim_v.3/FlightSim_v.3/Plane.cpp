/**
* \file Plane.cpp
* \brief Plik �r�d�owy klasy Plane
*/
#include "stdafx.h"
#include "Plane.h"
#include "Airport.h"


Plane::Plane()
{
	id = 1;
	next = NULL;
	this->position.x = position.x;
	this->position.y = position.y;
}

Plane::Plane(int initid, sf::Vector2f position)
{
	id = initid;
	next = NULL;
	this->position.x = position.x;
	this->position.y = position.y;
}


void Plane::move()
{
	Airport airport;
	/// Zmienna do skalowania pr�dko�ci
	int vscale = 1000;

	/// Logika ruchu samolotu, gdy l�duje
	if (state == PlaneState::LANDING)
	{
		/// Pocz�tkowe ustawienie pr�dko�ci podej�cia do l�dowania
		if (position.x <= 0)
		{
			velocity = (rand() % (1500 - 1000 + 1)) + 1000;
			position.x += velocity / vscale;
			scale = 1.5;
		}
		else
		{
			if (velocity > 1300) decelerate(5);
			else if (velocity > 1000) decelerate(2);
			else if (velocity > 300) decelerate(1);
			else if (velocity > 150) decelerate(-0.5);
			else if (velocity <= 150) velocity = 150;
			position.x += velocity / vscale;
			if (position.x < airport.lrunawayposition.x + 75 && scale >= 0.9) scale -= 0.002;
		}
	}

	/// Logika ruchu samolotu, gdy wylatuje
	if (state == PlaneState::DEPARTING)
	{
		/// Je�li samolot znajduje si� w hangarze ustawiamy jego pocz�tkow� wielko��, po�o�enie i pr�dko��
		if (position.x < airport.hangarposition.x + airport.hangarsize.x
			&& (rotation != windDirection || windDirection == 0))
		{
			scale = 0.9;
			velocity = 500;
			position.x = airport.hangarposition.x + airport.hangarsize.x;
		}

		/// Je�li samolot obr�ci� si� w kierunku wiatru niech przy�piesza
		if (rotation == windDirection && windDirection != 0)
		{
			accelerate(5);
			if (scale < 3) scale += 0.001;
			position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
			position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
		}

		/// Je�li wiatr wieje samolotowi w dziub od startu
		if (windDirection == 0)
		{
			if (position.x >= airport.hangarposition.x + airport.hangarsize.x
				&& position.x < airport.drunawayposition.x + airport.drunawaysize.y)
			{
				position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
				position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
			}
			else if (position.x >= airport.drunawayposition.x + airport.drunawaysize.y)
			{
				accelerate(5);
				if (scale < 3) scale += 0.001;
				position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
				position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
			}
		}

		/// Je�li samolot nie jest obr�cony w kierunku wiatru.
		/// Wyjazd z hangaru
		if (position.x >= airport.hangarposition.x + airport.hangarsize.x
			&& position.x < airport.drunawayposition.x + airport.drunawaysize.y
			&& rotation != windDirection)
		{
			position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
			position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
		}
		/// Je�li wyjecha� na odpowiedni� wysoko�� i nie jest obr�cony
		if (position.x >= airport.drunawayposition.x + airport.drunawaysize.y
			&& rotation != windDirection)
		{
			/// Je�liw wiatr wieje od 0 do -90 stopni
			if (windDirection < 0 && windDirection >= -90)
			{
				if (rotation > windDirection)
				{
					rotation -= 0.5;
					position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
					position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
				}
			}

			/// Je�li wiatr wieje od zera do 90 stopni
			if (windDirection > 0 && windDirection <= 90)
			{
				if (rotation < windDirection)
				{
					rotation += 0.5;
					position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
					position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
				}
			}

			/// Je�li wiatr wieje w kierunku od -180 do -90 stopni
			if (windDirection < -90 && windDirection >= -180)
			{
				/// Niech samolot wyjedzie dalej przed ustawienie si� w linii wiatru
				if (position.x<airport.drunawayposition.x + 3 * airport.drunawaysize.y && rotation != windDirection)
				{
					position.x += (velocity / vscale);
				}
				/// Je�li wyjecha� niech ustawi si� w linii wiatru
				else if (position.x >= airport.drunawayposition.x + 3 * airport.drunawaysize.y && rotation != windDirection)
				{
					if (rotation > windDirection)
					{
						rotation -= 0.5;
						position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
						position.y += ((velocity + 500) / vscale)*sin((rotation * 3.14) / 180.0f);
					}
				}
			}

			/// Je�li wiatr wieje w kierunku od 90 do 180 stopni
			if (windDirection > 90 && windDirection <= 180)
			{
				/// NIech samolot wyjedzie dalej przed ustawienie si� w lini wiatru
				if (position.x < airport.drunawayposition.x + 3 * airport.drunawaysize.y && rotation != windDirection)
				{
					position.x += (velocity / vscale);
				}
				/// Je�li wyjecha� niech si� ustawi w linii wiatru
				else if (position.x >= airport.drunawayposition.x + 3 * airport.drunawaysize.y && rotation != windDirection)
				{
					if (rotation < windDirection)
					{
						rotation += 0.5;
						position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
						position.y += ((velocity + 500) / vscale)*sin((rotation * 3.14) / 180.0f);
					}
				}
			}
		}
	}
}




