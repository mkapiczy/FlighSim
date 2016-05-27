/**
* \file Engine.cpp
* \brief Plik Ÿród³owy klasy Engine
*/

#include "stdafx.h"
#include "Engine.h"
#include "Airport.h"
#include "Plane.h"
#include "GraphicEngine.h"
#include "Simulation.h"
#include "Bus.h"

using namespace std;


Engine::Engine()
{
	gengine = new GraphicEngine();
}

Engine::~Engine()
{
	delete gengine;
}


void Engine::menu()
{
	gengine->gMenu();
}


void Engine::airport()
{
	/// Prawdopodobieñstwa pojawienia siê samolotu do l¹dowania i prawdopodobieñstwo wyst¹pienia proœby o wylot
	double pland = 0.35;
	double pdepart = 0.35;
	double pbus = 0.8;

	srand((unsigned)time(NULL));

	/// Inicjalizacja wiatru
	wind->randomWindChange();

	/// Losowa inicjalizacja samolotów na lotnisku
	int *id = new int();
	vector<int> check;
	bool *c = new bool();
	*c = false;

	for (int i = 0; i < Airport::MAX_CAPACITY - 2; i++)
	{
		/// 50% szans ¿e ka¿de z miejsc w hangarze zostanie zajête
		int r = (rand() % (1 - 0 + 1)) + 0;
		if (r == 1)
		{
			/// Losowy dobór id. Losowanie bez powtórzeñ
			do
			{
				*id = (rand() % (500 - 2 + 1)) + 2;
				for (int j = 0; j < check.size(); j++)
				{
					if (check[j] == *id)
					{
						*c = true;
					}
				}

			} while (*c == true);

			check.push_back(*id);

			plane = new Plane(*id, { 0, 360 });
			atairport.addPlane(plane);
			tolanding.nPlanes = i + 1;
			delete plane;
		}
	}

	/// Pokazanie stanu lotniska
	atairport.show();

	/// Flagi zajêcia pasów do l¹dowania i odlotu
	bool landed = false;
	bool departed = false;
	bool landingflag = false;
	bool departingflag = false;
	bool flightnow = false;
	bool myplaneflag = false;
	bool bustolanding = false;
	bool bustodeparting = false;
	bool busfromlanding = false;
	bool busfromdeparting = false;
	bool buslanded = false;
	bool busdeparted = false;

	/// Zegary do odmierzania czasów
	sf::Clock zegar1;
	sf::Clock zegar2;
	sf::Clock land;
	sf::Clock depart;
	sf::Clock windclock;
	sf::Clock busclock;

	/// Flaga symulacji
	bool simulation = true;

	/// G³ówna pêtla symulacji
	while (simulation)
	{
		/// Obs³uga eventów
		sf::Event event;
		while (gengine->window->pollEvent(event))
		{
			/// Wyjscie z programu przez nacisniecie przycisku Escape
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			{
				simulation = false;
				Simulation::simState = Simulation::SimState::MENU;
				/// Czyszczenie list
				tolanding.clear();
				landing.clear();
				atairport.clear();
				todeparting.clear();
				departing.clear();
				buslandingqueue.clearbus();
				busatdeparting.clearbus();
				busdepartingqueue.clearbus();
				busatdeparting.clearbus();
				myplaneflag = false;
				check.clear();
				return;
			}
			/// Przejscie do symulacji lotu
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space && myplaneflag == false)
			{
				myplaneflag = true;
				myplane = new MyPlane(1, { 640, 360 });
				todeparting.addPlane(myplane);
				atairport.show();
				cout << "Samolot " << todeparting.back->id << " prosi o pozwolenie na wylot." << endl;
				if (departing.runaway() == false)
				{
					cout << "Nie ma pozwolenia na wylot! Pas zajety! Proszê czekaæ" << endl;
				}
			}
		}

		sf::Time t1 = zegar1.getElapsedTime();
		sf::Time t2 = zegar2.getElapsedTime();
		sf::Time windTime = windclock.getElapsedTime();

		/// Zmiana stanu flagi l¹dowania
		if (landing.empty() == true)
		{
			landed = false;
		}

		/// Zmiana stanu flagi wylotu
		if (departing.empty() == true)
		{
			departed = false;
		}

		/// Zmiana stanu flagi autobusu w przestrzeni ladowania
		if (busatlanding.count == 0)
		{
			buslanded = false;
		}
		/// Zmiana stanu flagi autobusu w przestrzeni wylotow
		if (busatdeparting.count == 0)
		{
			busdeparted = false;
		}

		/// Losowa zmiana prêdkoœci i kierunku wiatru raz na 15 sekund
		if (windTime.asSeconds() > 15)
		{
			wind->randomWindChange();
			windclock.restart();
		}

		/// Logika ruchu autobusów
		sf::Time busTime = busclock.getElapsedTime();

		if (busTime.asSeconds() > 5)
		{
			static int i = 0;
			double r = (static_cast<double>(rand())) / (RAND_MAX);
			static int random1, random2;
			if (r <= pbus)
			{
				/// Jesli nie ma autobusu na pasie do ladowania i na pasie do wylotow i zaden nie czeka juz w kolejce
				if (busatlanding.count == 0 && busatdeparting.count == 0 && buslandingqueue.count == 0)
				{
					/// Program losuje liczbe 1 lub 2
					random1 = (rand() % (2 - 1 + 1) + 1);
					/// Jesli jeden to autobus jedzie "do hangaru" po pasie do ladowania
					if (random1 == 1)
					{
						bus = new Bus(1, { 120, 580 });
						buslandingqueue.addBus(bus);
						cout << "Autobus chce wjechaæ w teren ladowania." << endl;
					}
					/// Jesli jeden to autobus jedzie "od hangaru" po pasie do ladowania
					if (random1 == 2)
					{
						bus = new Bus(1, { static_cast<float>(atairport.hangarposition.x), 360 });
						buslandingqueue.addBus(bus);
						cout << "Autobus chce wjechaæ w teren ladowania." << endl;
					}
				}
				/// Jesli nie ma autobusu na pasie do ladowania i na pasie do wylotow i zaden nie czeka juz w kolejce 
				if (busatdeparting.count == 0 && busatlanding.count == 0 && busdepartingqueue.count == 0)
				{
					/// Program losuje liczbe calkowita od 1 do 3
					random2 = (rand() % (3 - 1 + 1) + 1);
					/// Jesli wylosowana liczba to 3 to autobus zglasza chec wjechania w obszar wylotow
					if (random2 == 3)
					{
						bus = new Bus(1, { 120, 580 });
						busdepartingqueue.addBus(bus);
						cout << "Autobus chce wjechaæ w teren wylotow." << endl;
					}
				}

				/// Wierza sprawdza stan lotniska i wydaje, badz nie pozwolenie na wjazd przez autobusy
				if (random1 == 1 && buslandingqueue.count > 0)
				{
					if ((landing.empty() == true && tolanding.count == 0 && busatlanding.count == 0 && busatdeparting.count == 0))
					{
						cout << "Autobus otrzymuje pozwolenie na wjazd w teren l¹dowania" << endl;
						busatlanding.addBus(buslandingqueue.busfront);
						busatlanding.busback->state = Bus::BusState::BUSTOLANDING;
						buslandingqueue.removeBus();
						bustolanding = true;
						i = 0;
					}
					else if (i == 0)
					{
						cout << "Autobus: " << " nie otrzymuje pozwolenia na wjazd w obszar l¹dowania! Obszar zajêty!" << endl;
						i = 1;
					}
				}

				if (random1 == 2 && buslandingqueue.count > 0)
				{
					if ((landing.empty() == true && tolanding.count == 0 && busatlanding.count == 0 && busatdeparting.count == 0))
					{
						cout << "Autobus otrzymuje pozwolenie na wjazd w teren l¹dowania" << endl;
						busatlanding.addBus(buslandingqueue.busfront);
						busatlanding.busback->state = Bus::BusState::BUSFROMLANDING;
						busfromlanding = true;
						i = 0;
					}
					else if (i == 0)
					{
						cout << "Autobus: " << " nie otrzymuje pozwolenia na wjazd w obszar l¹dowania! Obszar zajêty!" << endl;
						i = 1;
					}
				}

				if (random2 == 3 && busdepartingqueue.count > 0)
				{
					if ((departing.empty() == true && todeparting.count == 0 && busatdeparting.count == 0 && busatlanding.count == 0))
					{
						cout << "Autobus otrzymuje pozwolenie na wjazd w teren wylotow" << endl;
						busatdeparting.addBus(busdepartingqueue.busfront);
						busatdeparting.busback->state = Bus::BusState::BUSTODEPARTING;
						busdepartingqueue.removeBus();
						bustodeparting = true;
						i = 0;
					}
					else if (i == 0)
					{
						cout << "Autobus: " << " nie otrzymuje pozwolenia na wjazd w obszar wylotow! Obszar zajêty!" << endl;
						i = 1;
					}
				}
				busclock.restart();
			}
		}

		if (buslanded == true)
		{
			bustolanding = false;
			busfromlanding = false;
			cout << "Autobus opuscil przestrzen ladowania" << endl;
			busatlanding.removeBus();
		}

		if (busdeparted == true)
		{
			bustodeparting = false;
			busfromdeparting = false;
			cout << "Autobus opuscil przestrzen wylotow" << endl;
			busatdeparting.removeBus();
		}


		/// Logika l¹dowania
		if ((t1.asSeconds()) > 4)
		{
			if (tolanding.count <= 2)
			{
				/// Prawdopodobienstwo pojawienia sie samolotu chetnego na ladowanie
				double r = (static_cast<double>(rand())) / (RAND_MAX);
				if (r <= pland)
				{
					/// Losowe przydzielenie id samolotowi poprzez losowanie bez powtorzen
					do
					{
						*id = (rand() % (500 - 2 + 1)) + 2;
						for (int j = 0; j < check.size(); j++)
						{
							if (check[j] == *id)
							{
								*c = true;
							}
						}

					} while (*c == true);

					check.push_back(*id);

					plane = new Plane(*id, { 0, 360 });
					tolanding.addPlane(plane);
					delete plane;
					cout << "Samolot " << tolanding.back->id << " prosi o pozwolenie na ladowanie. " << endl;
				}
			}
			/// Jesli jakis samolot czeka w kolejce do ladowania
			if (tolanding.empty() == false)
			{
				/// Gdy lotnisko jest pelne
				if (atairport.full() == true)
				{
					atairport.refuse();
					cout << "Samolot zostaje skierowany do innego lotniska! " << endl;
					if (tolanding.count > 0) tolanding.removePlane();
				}
				else
				{
					/// Jesli pas do ladowania jest wolny
					if (landing.runaway() == true && bustolanding == false && busfromlanding == false)
					{
						landingflag = true;
						land.restart();
						cout << "Samolot " << tolanding.front->id << " otrzymuje pozwolenie na l¹dowanie. " << endl;

						landed = false;
						landing.addPlane(tolanding.front);
						landing.back->position.x = 0;
						landing.back->position.y = 360;
						landing.back->state = Plane::PlaneState::LANDING;
						tolanding.removePlane();
						cout << "Samolot " << landing.back->id << " jest w trakcie ladowania" << endl;
					}
					else
					{
						cout << "Samolot: " << tolanding.back->id << " nie otrzymuje pozwolenia na ladowanie! Pas zajety! Samolot jest " << tolanding.count << " w kolejce" << endl;
					}
				}
			}
			/// Restart zegara
			zegar1.restart();
		}

		if (landed == true)
		{
			landingflag = false;
			if (landing.front->id != 1)
			{
				atairport.addPlane(landing.front);
				atairport.land(atairport.back);
				atairport.back->state = Plane::PlaneState::PARKED;
			}
			if (landing.front->id == 1)
			{
				atairport.land(landing.front);
			}
			landing.removePlane();
			cout << "*****" << endl;
			atairport.show();
			land.restart();
		}

		/// Logika wylotów
		if (t2.asSeconds() > 4.5)
		{
			double r = (static_cast<double>(rand())) / (RAND_MAX);
			if (r <= pdepart)
			{
				/// Jesli lotnisko jest puste
				if (atairport.empty() == true)
				{
					/// Nie ma kto wyleciec, wiec nic nie rob.
				}
				/// Jesli ktos jest na lotnisku
				else if (atairport.empty() == false && todeparting.count <= 1)
				{
					todeparting.addPlane(atairport.front);
					atairport.removePlane();
					cout << "Samolot " << todeparting.back->id << " prosi o pozwolenie na wylot." << endl;
				}
			}
			/// Jesli ktos czeka w kolejce do wyloty
			if (todeparting.empty() == false) 
			{
				/// Jesli pas do wylotu jest wolny
				if (departing.runaway() == true && bustodeparting == false) 
				{
					cout << "Samolot " << todeparting.front->id << " otrzymuje pozwolenie na wylot." << endl;
					if (todeparting.front->id == 1)
					{
						flightnow = true;
					}
					departingflag = true;
					departing.addPlane(todeparting.front);
					departing.back->windDirection = Wind::direction;
					departing.back->state = Plane::PlaneState::DEPARTING;
					todeparting.removePlane();
					cout << "Samolot " << departing.front->id << " jest w trakcie startu" << endl;
				}
				else
				{
					cout << "Samolot " << todeparting.back->id << " nie ma pozwolenia na wylot! Pas zajety! Samolot jest " << todeparting.count << " w kolejce" << endl;
				}
			}
			zegar2.restart();
		}

		if (departed == true)
		{
			departing.depart(departing.front);
			departing.removePlane();
			depart.restart();
			departingflag = false;
			departed = true;
			atairport.show();

			if (flightnow == true)
			{
				Simulation::simState = Simulation::SimState::FLIGHT;
				/// Czyszczenie list
				tolanding.clear();
				landing.clear();
				atairport.clear();
				todeparting.clear();
				departing.clear();
				check.clear();
				myplaneflag = false;
				return;
			}
		}

		/// Rysowanie i ruch samolotów

		/// Przypadek, gdy samolot tylko laduje
		if (landingflag == true && landed == false && departingflag == false && bustolanding == false && bustodeparting == false && busfromlanding == false && busfromdeparting == false)
		{
			if (landing.front->position.x < atairport.hangarposition.x + 15)
			{
				landing.back->move();
				gengine->gAirport(landing.front);
			}
			else
			{
				landingflag = false;
				landed = true;
			}
		}

		/// Przypadek, gdy samolot l¹duje, a autobus jest na pasie do wylotu
		if (landingflag == true && landed == false && departingflag == false && bustolanding == false && bustodeparting == true)
		{
			if ((busatdeparting.busfront->position.x < atairport.hangarposition.x + 20) || (busatdeparting.busfront->position.x >= atairport.hangarposition.x + 30
				|| busatdeparting.busfront->position.y > 370))
			{
				landing.back->move();
				busatdeparting.busback->move();
				gengine->gAirport(landing.front, busatdeparting.busfront);
			}
			else
			{
				bustodeparting = false;
				busdeparted = true;
			}

			if (landing.front->position.x < atairport.hangarposition.x + 15)
			{
				landing.back->move();
				busatdeparting.busback->move();
				gengine->gAirport(landing.front, busatdeparting.busfront);
			}
			else
			{
				landingflag = false;
				landed = true;
			}
		}

		/// Przypadek, gdy tylko autobus jest na pasie do l¹dowania
		if ((bustolanding == true || busfromlanding == true) && landingflag == false && departingflag == false)
		{
			if (bustolanding == true)
			{
				if (busatlanding.busfront->position.x < atairport.hangarposition.x + 50)
				{
					busatlanding.busback->move();
					gengine->gAirport(busatlanding.busfront);
				}
				else
				{
					bustolanding = false;
					buslanded = true;
				}
			}

			if (busfromlanding == true)
			{
				if (busatlanding.busfront->position.y < atairport.busstopposition.y + 20)
				{
					busatlanding.busback->move();
					gengine->gAirport(busatlanding.busfront);
				}
				else
				{
					busfromlanding = false;
					buslanded = true;
				}
			}
		}

		/// Przypadek, gdy tylko samolot startuje
		if (departingflag == true && departed == false && landingflag == false && bustolanding == false && busfromlanding == false && bustodeparting == false
			&& busfromdeparting == false)
		{
			if (departing.front->position.x < 1280 + 20 && departing.front->position.y > -20 && departing.front->position.y < 720 + 20
				&& departing.front->position.x > -20)
			{
				departing.back->move();
				gengine->gAirport(departing.front);
			}
			else
			{
				departingflag = false;
				departed = true;
			}
		}

		/// Przypadek, gdy tylko autobus jest na pasie do wylotu
		if (bustodeparting == true && landingflag == false && departingflag == false)
		{
			if ((busatdeparting.busfront->position.x < atairport.hangarposition.x + 20) || (busatdeparting.busfront->position.x >= atairport.hangarposition.x + 30
				|| busatdeparting.busfront->position.y > 370))
			{
				busatdeparting.busback->move();
				gengine->gAirport(busatdeparting.busfront);
			}
			else
			{
				bustodeparting = false;
				busdeparted = true;
			}
		}

		/// Przypadek, gdy samolot startuje, a autobus jest na pasie do l¹dowania
		if (landingflag == false && departingflag == true && (bustolanding == true || busfromlanding == true) && buslanded == false)
		{
			if (departing.front->position.x < 1280 + 20 && departing.front->position.y > -20 && departing.front->position.y < 720 + 20
				&& departing.front->position.x > -20)
			{
				departing.back->move();
				busatlanding.busback->move();
				gengine->gAirport(departing.front, busatlanding.busfront);
			}
			else
			{
				departingflag = false;
				departed = true;
			}

			if (bustolanding == true)
			{
				if (busatlanding.busfront->position.x < atairport.hangarposition.x + 50)
				{
					departing.back->move();
					busatlanding.busback->move();
					gengine->gAirport(departing.front, busatlanding.busfront);
				}
				else
				{
					bustolanding = false;
					buslanded = true;
				}


				if (busfromlanding == true)
				{
					if (busatlanding.busfront->position.y < atairport.busstopposition.y + 20)
					{
						departing.back->move();
						busatlanding.busback->move();
						gengine->gAirport(departing.front, busatlanding.busfront);
					}
					else
					{
						busfromlanding = false;
						buslanded = true;
					}
				}
			}
		}

		/// Przypadek, gdy samolotu startuj¹ i l¹duj¹ jednoczeœnie
		if ((departingflag == true && departed == false) && (landingflag == true && landed == false) && bustolanding == false && busfromlanding == false
			&& bustodeparting == false && busfromdeparting == false)
		{
			if (departing.front->position.x < 1280 + 50 && departing.front->position.y > -20 && departing.front->position.y < 720 + 20
				&& departing.front->position.x > -20)
			{
				landing.back->move();
				departing.back->move();
				gengine->gAirport(landing.front, departing.front);
			}
			else
			{
				departingflag = false;
				departed = true;
			}

			if (landing.front->position.x < atairport.hangarposition.x + 15)
			{
				landing.back->move();
				departing.back->move();
				gengine->gAirport(landing.front, departing.front);
			}
			else
			{
				landingflag = false;
				landed = true;
			}

		}

		/// Przypadek, gdy na lotnisku nic sie nie dzieje
		if (landingflag == false && departingflag == false && bustolanding == false && busfromlanding == false && bustodeparting == false && busfromdeparting == false)
		{
			gengine->gAirport();
		}

		/// Restart zegarow
		if (zegar1.getElapsedTime().asSeconds() > 15) zegar1.restart();
		if (zegar2.getElapsedTime().asSeconds() > 15) zegar2.restart();
	}

	/// Czyszczenie
	delete id;
	delete c;
}

void Engine::flight()
{
	myplane = new MyPlane(1, { 640, 1950 });
	myplane->velocity = 400;
	myplane->rotation = -10;
	myplane->state = MyPlane::State::ASCENDING;

	/// Inicjalizacja wiatru
	wind->randomWindChange();
	myplane->windSpeed = Wind::speed;
	myplane->windDirection = Wind::direction;

	/// Zegary symulacji
	sf::Clock windclock, clock, fuelclock;
	/// Flaga symulacji
	bool simulation = true;

	/// Glowna petla symulacji
	while (simulation)
	{
		/// Obs³uga eventów
		sf::Event event;
		while (gengine->window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			{
				simulation = false;
				Simulation::simState = Simulation::SimState::MENU;
				/// Czyszczenie list
				tolanding.clear();
				landing.clear();
				atairport.clear();
				todeparting.clear();
				departing.clear();
				return;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				MyPlane::state = MyPlane::State::ASCENDING;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
			{
				MyPlane::state = MyPlane::State::DESCENDING;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				MyPlane::state = MyPlane::State::MAINTAINING;
			}
		}


		sf::Time windTime = windclock.getElapsedTime();
		/// Losowa zmiana prêdkoœci i kierunku wiatru
		if (windTime.asSeconds() > 10)
		{
			wind->randomWindChange();
			myplane->windSpeed = Wind::speed;
			myplane->windDirection = Wind::direction;
			windclock.restart();
		}

		sf::Time fuelTime = fuelclock.getElapsedTime();
		if (fuelTime.asMilliseconds() > 100)
		{
			myplane->consumefuel();
		}
		/// Podejscie do ladowania
		if (MyPlane::state == MyPlane::LANDING)
		{
			/// Zmiana stanu symulacji
			Simulation::simState = Simulation::SimState::AIRPORT;

			/// Losowa inicjalizacja samolotów na lotnisku
			int *id = new int();
			vector<int> check;
			bool *c = new bool();
			*c = false;

			for (int i = 0; i < 2; i++)
			{
				/// 50% szans ¿e ka¿de z miejsc w hangarze zostanie zajête
				int r = (rand() % (1 - 0 + 1)) + 0;
				if (r == 1)
				{
					/// Losowy dobór id. Losowanie bez powtórzeñ
					do
					{
						*id = (rand() % (500 - 2 + 1)) + 2;
						for (int j = 0; j < check.size(); j++)
						{
							if (check[j] == *id)
							{
								*c = true;
							}
						}

					} while (*c == true);

					check.push_back(*id);

					plane = new Plane(*id, { 0, 360 });
					tolanding.addPlane(plane);
					tolanding.nPlanes = i + 1;
					delete plane;
					cout << "Samolot " << tolanding.front->id << " prosi o pozwolenie na ladowanie. " << endl;
				}
			}
			cout << "--DO LADOWANIA--" << endl;
			tolanding.show();

			tolanding.addPlane(myplane);
			cout << "Samolot " << tolanding.back->id << " prosi o pozwolenie na ladowanie. " << endl;
			if (tolanding.count > 1)
			{
				cout << "Nie ma pozwolenia na ladowanie! Pas zajety! Samolot jest " << tolanding.count << " w kolejce" << endl;
			}
			return;
		}

		double dt = clock.restart().asMilliseconds();
		myplane->move(dt / 1000);
		gengine->gFlight(myplane);

	}
}
