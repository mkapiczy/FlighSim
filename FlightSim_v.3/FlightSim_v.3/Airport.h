/**
* \file Airport.h
* \brief Plik nag³owkowy klasy Airport
*/

#pragma once
#include "Plane.h"
#include "Vehicle.h"
#include "Bus.h"

using namespace std;

/** \brief Klasa reprezentujaca lotnisko
*
* Definicja klasy Airport
*/

class Airport
{
public:
	/// Konstruktor
	Airport();
	/// Destruktor
	~Airport();
	/** \brief Dodanie samolotu do listy
	*
	* Funkcja odpowiadajaca za dodanie samolotu do listy jednokierunkowej
	* \param plane wskaŸnik do obiektu klasy Plane, który ma zostaæ dodany do listy
	*/
	void addPlane(Plane *plane); 
	/** \brief Usuniecie samolotu z listy
	*
	* Funkcja odpowiadajaca za usuniecie samolotu z listy jednokierunkowej
	*/
	void removePlane();
	/** \brief Czyszczenie listy
	*
	* Funkcja odpowiadajaca za wyczyszczenie listy jednokierunkowej
	*/
	void clear();
	/** \brief Pokazanie zawartosci listy
	*
	* Funkcja odpowiadajaca za pokazanie zawartosci listy jednokierunkowej
	*/
	void show(); 
	/** \brief Odmowa wylotu/przylotu
	*
	* Funkcja wyswietla komunikat o odmowie wylotu/przylotu
	*/
	void refuse(); 
	/** \brief Lotnisko pelne
	*
	* Funkcja sprawdza, czy lista jednokierunkowa jest pelna (powyzej MAX_CAPACITY)
	* jesli tak zwraca true.
	*/
	bool full(); 
	/** \brief Lotnisko puste
	*
	* Funkcja sprawdza, czy lista jednokierunkowa jest pusta
	* jesli tak zwraca true.
	*/
	bool empty(); 
	/** \brief Pas wolny
	*
	* Funkcja sprawdza, czy lista jednokierunkowa reprezentujaca stan pasu jest pusta
	* jesli tak zwraca true.
	*/
	bool runaway(); 
	/** \brief Samolot wyladowal
	*
	* Funkcja wyswietla komunikat, gdy samolot wleci do "hangaru"
	*/
	void land(Vehicle *plane); // Pozwolenie na ladowanie
	/** \brief Samolot wylecial
	*
	* Funkcja wyswietla komunikat, gdy samolot opusci lotnisko
	*/
	void depart(Vehicle *plane);
	/** \brief Dodanie autobusu do listy
	*
	* Funkcja odpowiadajaca za dodanie autobusu do listy jednokierunkowej
	* \param bus wskaŸnik do obiektu klasy Bus, który ma zostaæ dodany do listy
	*/
	void addBus(Bus *bus);
	/** \brief Usuniecie autobusu z listy
	*	
	* Funkcja odpowiadajaca za usuniecie autobusu z listy jednokierunkowej
	*/
	void removeBus();
	/** \brief Czyszczenie listy
	*
	* Funkcja odpowiadajaca za wyczyszczenie listy jednokierunkowej
	*/
	void clearbus();
	/// Liczba elementow znajdujacych sie na liscie jednokierunkowej
	int count; 
	/// Maksymalna pojemnosc lotniska
	const static int MAX_CAPACITY=8; 
	/// Liczba obsluzonych przez lotnisko samolotow
	int nPlanes; 
	/// Wskazniki na poczatek i koniec listy jednokierunkowej typu Plane
	Plane *front, *back; 
	/// Wskazniki na poczatek i koniec listy jednokierunkowej typu Bus
	Bus *busfront, *busback;

	//Struktura lotniska
	const sf::Vector2i hangarposition = { 615, 185 };
	const sf::Vector2i hangarsize = { 50, 120 };
	const sf::Vector2i lrunawayposition = { 415, 300};
	const sf::Vector2i lrunawaysize = { 200, 120 };
	const sf::Vector2i drunawayposition = { 665,300 };
	const sf::Vector2i drunawaysize = { 200, 120 };
	const sf::Vector2i busstopposition = { 80, 560 };
};
