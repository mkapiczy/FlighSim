/**
* \file Plane.cpp
* \brief Plik Ÿród³owy klasy Plane
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
	/// Zmienna do skalowania prêdkoœci
	int vscale = 1000;

	/// Logika ruchu samolotu, gdy l¹duje
	if (state == PlaneState::LANDING)
	{
		/// Pocz¹tkowe ustawienie prêdkoœci podejœcia do l¹dowania
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
		/// Jeœli samolot znajduje siê w hangarze ustawiamy jego pocz¹tkow¹ wielkoœæ, po³o¿enie i prêdkoœæ
		if (position.x < airport.hangarposition.x + airport.hangarsize.x
			&& (rotation != windDirection || windDirection == 0))
		{
			scale = 0.9;
			velocity = 500;
			position.x = airport.hangarposition.x + airport.hangarsize.x;
		}

		/// Jeœli samolot obróci³ siê w kierunku wiatru niech przyœpiesza
		if (rotation == windDirection && windDirection != 0)
		{
			accelerate(5);
			if (scale < 3) scale += 0.001;
			position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
			position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
		}

		/// Jeœli wiatr wieje samolotowi w dziub od startu
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

		/// Jeœli samolot nie jest obrócony w kierunku wiatru.
		/// Wyjazd z hangaru
		if (position.x >= airport.hangarposition.x + airport.hangarsize.x
			&& position.x < airport.drunawayposition.x + airport.drunawaysize.y
			&& rotation != windDirection)
		{
			position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
			position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
		}
		/// Jeœli wyjecha³ na odpowiedni¹ wysokoœæ i nie jest obrócony
		if (position.x >= airport.drunawayposition.x + airport.drunawaysize.y
			&& rotation != windDirection)
		{
			/// Jeœliw wiatr wieje od 0 do -90 stopni
			if (windDirection < 0 && windDirection >= -90)
			{
				if (rotation > windDirection)
				{
					rotation -= 0.5;
					position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
					position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
				}
			}

			/// Jeœli wiatr wieje od zera do 90 stopni
			if (windDirection > 0 && windDirection <= 90)
			{
				if (rotation < windDirection)
				{
					rotation += 0.5;
					position.x += (velocity / vscale)*cos((rotation * 3.14) / 180.0f);
					position.y += (velocity / vscale)*sin((rotation * 3.14) / 180.0f);
				}
			}

			/// Jeœli wiatr wieje w kierunku od -180 do -90 stopni
			if (windDirection < -90 && windDirection >= -180)
			{
				/// Niech samolot wyjedzie dalej przed ustawienie siê w linii wiatru
				if (position.x<airport.drunawayposition.x + 3 * airport.drunawaysize.y && rotation != windDirection)
				{
					position.x += (velocity / vscale);
				}
				/// Jeœli wyjecha³ niech ustawi siê w linii wiatru
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

			/// Jeœli wiatr wieje w kierunku od 90 do 180 stopni
			if (windDirection > 90 && windDirection <= 180)
			{
				/// NIech samolot wyjedzie dalej przed ustawienie siê w lini wiatru
				if (position.x < airport.drunawayposition.x + 3 * airport.drunawaysize.y && rotation != windDirection)
				{
					position.x += (velocity / vscale);
				}
				/// Jeœli wyjecha³ niech siê ustawi w linii wiatru
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




