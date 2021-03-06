/**
* \file GraphicEngine.h
* \brief Plik nagłówkowy klasy GraphicEngine
*/

#pragma once

#include "Airport.h"
#include "Plane.h"
#include "MyPlane.h"
#include "Bus.h"

/** \brief Klasa reprezentujaca silnik graficzny programu
*
* Definicja klasy GraphicEngine
*/

class GraphicEngine
{
public:
	/// Konstruktor
	GraphicEngine();
	/// Destruktor
	~GraphicEngine();

	/** \brief Wizualizacja animacji lotniska
	*
	* Funkcja odpowiadająca za wizualizację lotniska
	*/
	void gAirport();
	/** \brief Wizualizacja animacji lotniska
	*
	* Funkcja odpowiadająca za wizualizację lotniska
	* \param plane Samolot na lotnisku
	*/
	void gAirport(Plane *plane);
	/** \brief Wizualizacja animacji lotniska
	*
	* Funkcja odpowiadająca za wizualizację lotniska
	* \param bus Autobus na lotnisku
	*/
	void gAirport(Bus *bus);
	/** \brief Wizualizacja animacji lotniska
	*
	* Funkcja odpowiadająca za wizualizację lotniska
	* \param plane1 Pierwszy samolot na lotnisku
	* \param plane2 Drugi samolot na lotnisku
	*/
	void gAirport(Plane *plane1, Plane *plane2);
	/** \brief Wizualizacja animacji lotniska
	*
	* Funkcja odpowiadająca za wizualizację lotniska
	* \param plane1 Pierwszy samolot na lotnisku
	* \param bus Autobus na lotnisku
	*/
	void gAirport(Plane *plane1, Bus *bus);
	/** \brief Wizualizacja animacji lotu
	*
	* Funkcja odpowiadająca za wizualizację symulacji lotu
	* \param myplane Samolot
	*/
	void gFlight(MyPlane *myplane);
	/** \brief Wizualizacja manu
	*
	* Funkcja odpowiadająca za wizualizację menu
	*/
	void gMenu();
	/** \brief Rysowanie tekstu na ekranie
	*
	* Funkcja odpowiadająca za rysowanie tekstu na ekranie
	* \param position miejsce, w którym zostanie narysowany tekst
	* \param text tekst do narysowania
	*/
	void gText(sf::Vector2f position, string text);
	/** \brief Załadowanie Sprite'a z pliku
	*
	* Funkcja odpowiadająca za załadowanie Sprite'a z obrazu z pliku
	* \param texture - tekstura obrazu
	* \param sprite - sprite obrazu
	* \param filename - nazwa pliku, z którego ma zostać wczytany obraz
	* \param position - pozycja sprite'a na ekranie
	*/
	sf::Sprite loadSprite(sf::Texture &texture, sf::Sprite &sprite, std::string filename, sf::Vector2i position);

	/// Okno wizualizacji
	sf::RenderWindow *window;
	
private:
	/// Rozdzielczość ekranu
	const sf::Vector2i screenDimension = { 1280, 720 };
	/// Tekstury obrazów
	sf::Texture airportTexture, lrunawayTexture, drunaway0Texture,drunawayTexture, hangarTexture, planeTexture, myplaneTexture, worldTexture
		, myplaneTexture2, myplaneTexture3, myplaneTexture4, busTexture, busstopTexture;
	/// Sprite'y obrazów
	sf::Sprite airportSprite, lrunawaySprite, drunaway0Sprite, drunawaySprite, hangarSprite, planeSprite, myplaneSprite,
		myplane2Sprite, myplane3Sprite, myplane4Sprite,worldSprite, busSprite, busstopSprite;
	/// Czcionka
	sf::Font font;
	/// Obiekt od obsługi zdarzeń np. wejścia klawiatury
	sf::Event event;
	/// Obiekt klasy Airport
	Airport *airport;
};

