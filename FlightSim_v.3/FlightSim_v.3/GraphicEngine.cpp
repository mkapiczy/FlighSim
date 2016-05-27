/**
* \file GraphicEngine.cpp
* \brief Plik Ÿród³owy klasy GraphicEngine
*/
#include "stdafx.h"
#include "GraphicEngine.h"
#include "Airport.h"
#include "Plane.h"
#include "Simulation.h"

using namespace std;


GraphicEngine::GraphicEngine()
{
	airport = new Airport();
	/// Zaladowanie ustawien obrazu
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	/// Stworzenie okna
	window = new sf::RenderWindow();
	window->create(sf::VideoMode(screenDimension.x, screenDimension.y), "FlightSim!", sf::Style::Default, settings);
	window->setFramerateLimit(200);

	// £adowanie czcionki z pliku
	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL, L"Font not found!", L"ERROR", NULL);
		return;
	}

	/// Zaladowanie potrzebnych Sprite'ow
	loadSprite(hangarTexture, hangarSprite, "hangar2.png",
	{ airport->hangarposition.x, airport->hangarposition.y });

	loadSprite(lrunawayTexture, lrunawaySprite, "runaway.png",
	{ airport->lrunawayposition.x - airport->lrunawaysize.x, airport->lrunawayposition.y });


	loadSprite(drunawayTexture, drunawaySprite, "runaway.png",
	{ airport->drunawayposition.x + airport->drunawaysize.x, airport->drunawayposition.y });

	loadSprite(airportTexture, airportSprite, "airport.png", { 0, 0 });

	loadSprite(worldTexture, worldSprite, "background4.png", { 0, 0 });

	loadSprite(planeTexture, planeSprite, "p1.png", { 0, 0 });

	loadSprite(myplaneTexture, myplaneSprite, "plane1.1.png", { 0, 0 });

	loadSprite(myplaneTexture2, myplane2Sprite, "plane1.2.png", { 0, 0 });

	loadSprite(myplaneTexture3, myplane3Sprite, "plane1.3.png", { 0, 0 });

	loadSprite(myplaneTexture4, myplane4Sprite, "plane2.png", { 0, 0 });

	loadSprite(busTexture, busSprite, "bus.png", { 0, 0 });

	loadSprite(busstopTexture, busstopSprite, "busstop.png", { airport->busstopposition.x, airport->busstopposition.y });
}


GraphicEngine::~GraphicEngine()
{
	delete window;
}

sf::Sprite GraphicEngine::loadSprite(sf::Texture &texture, sf::Sprite &sprite, std::string filename, sf::Vector2i position)
{
	string name = "data/images/" + filename + "";
	sf::Image img;
	img.loadFromFile(name);
	img.createMaskFromColor(sf::Color::White);
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setPosition(position.x, position.y);

	return sprite;
}

void GraphicEngine::gText(sf::Vector2f position, string text)
{
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(20);
	txt.setColor(sf::Color::Black);
	txt.setPosition(position);
	txt.setString(text);

	window->draw(txt);
}

void GraphicEngine::gMenu()
{
	sf::View kamera(sf::Vector2f(640, 360), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);

	sf::Text title("Symulator lotów FlightSim!", font, 80);
	title.setStyle(sf::Text::Bold);

	title.setPosition(screenDimension.x / 2 - title.getGlobalBounds().width / 2, 20);

	const int ile = 2;

	sf::Text tekst[ile];

	string str[] = { "Rozpocznij symulacje", "Wyjdz" };

	for (int i = 0; i < ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(screenDimension.x / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (Simulation::simState == Simulation::SimState::MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(*window));
		sf::Event event;

		while (window->pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
				Simulation::simState = Simulation::SimState::END;

			//klikniêcie SYMULACJI                              
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				Simulation::simState = Simulation::SimState::AIRPORT;
			}

			//klikniêcie EXIT
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				Simulation::simState = Simulation::SimState::END;
			}
		}
		for (int i = 0; i < ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(sf::Color::Cyan);
			else tekst[i].setColor(sf::Color::White);

			window->clear();

			window->draw(title);

			for (int i = 0; i < ile; i++)
				window->draw(tekst[i]);
			window->setView(kamera);
			window->display();
	}
}
void GraphicEngine::gAirport()
{
	sf::View kamera(sf::Vector2f(640, 360), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);
	sf::Sprite lrunaway0Sprite(drunawaySprite);
	lrunaway0Sprite.setPosition(airport->lrunawayposition.x, airport->lrunawayposition.y);
	sf::Sprite drunaway0Sprite(drunawaySprite);
	drunaway0Sprite.setPosition(airport->drunawayposition.x, airport->drunawayposition.y);

	window->clear();
	window->draw(airportSprite);
	window->draw(lrunaway0Sprite);
	window->draw(lrunawaySprite);
	window->draw(drunaway0Sprite);
	window->draw(drunawaySprite);
	window->draw(hangarSprite);
	window->draw(busstopSprite);
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 290 }, "Predkosc wiatru: " + to_string((Wind::speed)));
	string direct;
	if (Wind::direction == 0) direct = "wschodni";
	if (Wind::direction == -90) direct = "polnocny";
	if (Wind::direction == 90) direct = "poludniowy";
	if (Wind::direction == -180 || Wind::direction == 180) direct = "zachodni";
	if (Wind::direction > 0 && Wind::direction < 90) direct = to_string(Wind::direction) + " stopni poludniowy-wschod";
	if (Wind::direction > -90 && Wind::direction < 0) direct = to_string(Wind::direction) + " stopni polnocny-wschod";
	if (Wind::direction > -180 && Wind::direction < -90) direct = to_string(Wind::direction) + " stopni polnocny-zachod";
	if (Wind::direction > 90 && Wind::direction < 180) direct = to_string(Wind::direction) + " stopni poludniowy-zachod";
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 270 }, "Kierunek wiatru: " + direct);
	window->display();
}

void GraphicEngine::gAirport(Plane *plane)
{
	sf::View kamera(sf::Vector2f(640, 360), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);
	sf::Sprite lrunaway0Sprite(drunawaySprite);
	lrunaway0Sprite.setPosition(airport->lrunawayposition.x, airport->lrunawayposition.y);
	sf::Sprite drunaway0Sprite(drunawaySprite);
	drunaway0Sprite.setPosition(airport->drunawayposition.x, airport->drunawayposition.y);
	planeSprite.setOrigin(20, 20);
	planeSprite.setPosition(plane->position);
	planeSprite.setRotation(plane->rotation);
	planeSprite.setScale({ static_cast<float>(plane->scale), static_cast<float>(plane->scale) });

	window->clear();
	window->draw(airportSprite);
	window->draw(lrunaway0Sprite);
	window->draw(lrunawaySprite);
	window->draw(drunaway0Sprite);
	window->draw(drunawaySprite);
	window->draw(busstopSprite);
	window->draw(planeSprite);
	window->draw(hangarSprite);
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 290 }, "Predkosc wiatru: " + to_string((Wind::speed)));
	string direct;
	if (Wind::direction == 0) direct = "wschodni";
	if (Wind::direction == -90) direct = "polnocny";
	if (Wind::direction == 90) direct = "poludniowy";
	if (Wind::direction == -180 || Wind::direction == 180) direct = "zachodni";
	if (Wind::direction > 0 && Wind::direction < 90) direct = to_string(Wind::direction) + " stopni poludniowy-wschod";
	if (Wind::direction > -90 && Wind::direction < 0) direct = to_string(Wind::direction) + " stopni polnocny-wschod";
	if (Wind::direction > -180 && Wind::direction < -90) direct = to_string(Wind::direction) + " stopni polnocny-zachod";
	if (Wind::direction > 90 && Wind::direction < 180) direct = to_string(Wind::direction) + " stopni poludniowy-zachod";
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 270 }, "Kierunek wiatru: " + direct);
	window->display();
}

void GraphicEngine::gAirport(Bus *bus)
{
	sf::View kamera(sf::Vector2f(640, 360), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);
	sf::Sprite lrunaway0Sprite(drunawaySprite);
	lrunaway0Sprite.setPosition(airport->lrunawayposition.x, airport->lrunawayposition.y);
	sf::Sprite drunaway0Sprite(drunawaySprite);
	drunaway0Sprite.setPosition(airport->drunawayposition.x, airport->drunawayposition.y);
	busSprite.setOrigin(20, 8);
	busSprite.setPosition(bus->position);
	busSprite.setRotation(bus->rotation);

	window->clear();
	window->draw(airportSprite);
	window->draw(lrunaway0Sprite);
	window->draw(lrunawaySprite);
	window->draw(drunaway0Sprite);
	window->draw(drunawaySprite);
	window->draw(busSprite);
	window->draw(busstopSprite);
	window->draw(hangarSprite);
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 290 }, "Predkosc wiatru: " + to_string((Wind::speed)));
	string direct;
	if (Wind::direction == 0) direct = "wschodni";
	if (Wind::direction == -90) direct = "polnocny";
	if (Wind::direction == 90) direct = "poludniowy";
	if (Wind::direction == -180 || Wind::direction == 180) direct = "zachodni";
	if (Wind::direction > 0 && Wind::direction < 90) direct = to_string(Wind::direction) + " stopni poludniowy-wschod";
	if (Wind::direction > -90 && Wind::direction < 0) direct = to_string(Wind::direction) + " stopni polnocny-wschod";
	if (Wind::direction > -180 && Wind::direction < -90) direct = to_string(Wind::direction) + " stopni polnocny-zachod";
	if (Wind::direction > 90 && Wind::direction < 180) direct = to_string(Wind::direction) + " stopni poludniowy-zachod";
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 270 }, "Kierunek wiatru: " + direct);
	window->display();
}

void GraphicEngine::gAirport(Plane *plane1, Bus *bus)
{
	sf::View kamera(sf::Vector2f(640, 360), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);
	sf::Sprite lrunaway0Sprite(drunawaySprite);
	lrunaway0Sprite.setPosition(airport->lrunawayposition.x, airport->lrunawayposition.y);
	sf::Sprite drunaway0Sprite(drunawaySprite);
	drunaway0Sprite.setPosition(airport->drunawayposition.x, airport->drunawayposition.y);


	planeSprite.setOrigin(20, 20);
	busSprite.setOrigin(20, 8);
	planeSprite.setPosition(plane1->position);
	busSprite.setPosition(bus->position);
	planeSprite.setRotation(plane1->rotation);
	busSprite.setRotation(bus->rotation);
	planeSprite.setScale({ static_cast<float>(plane1->scale), static_cast<float>(plane1->scale) });
	//busSprite.setScale({ static_cast<float>(bus->scale), static_cast<float>(plane2->scale) });

	window->clear();
	window->draw(airportSprite);
	window->draw(lrunaway0Sprite);
	window->draw(lrunawaySprite);
	window->draw(drunaway0Sprite);
	window->draw(drunawaySprite);
	window->draw(busSprite);
	window->draw(busstopSprite);
	window->draw(planeSprite);
	window->draw(hangarSprite);
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 290 }, "Predkosc wiatru: " + to_string((Wind::speed)));
	string direct;
	if (Wind::direction == 0) direct = "wschodni";
	if (Wind::direction == -90) direct = "polnocny";
	if (Wind::direction == 90) direct = "poludniowy";
	if (Wind::direction == -180 || Wind::direction == 180) direct = "zachodni";
	if (Wind::direction > 0 && Wind::direction < 90) direct = to_string(Wind::direction) + " stopni poludniowy-wschod";
	if (Wind::direction > -90 && Wind::direction < 0) direct = to_string(Wind::direction) + " stopni polnocny-wschod";
	if (Wind::direction > -180 && Wind::direction < -90) direct = to_string(Wind::direction) + " stopni polnocny-zachod";
	if (Wind::direction > 90 && Wind::direction < 180) direct = to_string(Wind::direction) + " stopni poludniowy-zachod";
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 270 }, "Kierunek wiatru: " + direct);
	window->display();
}

void GraphicEngine::gAirport(Plane *plane1, Plane *plane2)
{
	sf::View kamera(sf::Vector2f(640, 360), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);
	sf::Sprite lrunaway0Sprite(drunawaySprite);
	lrunaway0Sprite.setPosition(airport->lrunawayposition.x, airport->lrunawayposition.y);
	sf::Sprite drunaway0Sprite(drunawaySprite);
	drunaway0Sprite.setPosition(airport->drunawayposition.x, airport->drunawayposition.y);

	sf::Sprite plane2Sprite(planeSprite);
	planeSprite.setOrigin(20, 20);
	plane2Sprite.setOrigin(20, 20);
	planeSprite.setPosition(plane1->position);
	plane2Sprite.setPosition(plane2->position);
	planeSprite.setRotation(plane1->rotation);
	plane2Sprite.setRotation(plane2->rotation);
	planeSprite.setScale({ static_cast<float>(plane1->scale), static_cast<float>(plane1->scale) });
	plane2Sprite.setScale({ static_cast<float>(plane2->scale), static_cast<float>(plane2->scale) });

	window->clear();
	window->draw(airportSprite);
	window->draw(lrunaway0Sprite);
	window->draw(lrunawaySprite);
	window->draw(drunaway0Sprite);
	window->draw(drunawaySprite);
	window->draw(busstopSprite);
	window->draw(planeSprite);
	window->draw(plane2Sprite);
	window->draw(hangarSprite);
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 290 }, "Predkosc wiatru: " + to_string((Wind::speed)));
	string direct;
	if (Wind::direction == 0) direct = "wschodni";
	if (Wind::direction == -90) direct = "polnocny";
	if (Wind::direction == 90) direct = "poludniowy";
	if (Wind::direction == -180 || Wind::direction == 180) direct = "zachodni";
	if (Wind::direction > 0 && Wind::direction < 90) direct = to_string(Wind::direction) + " stopni poludniowy-wschod";
	if (Wind::direction > -90 && Wind::direction < 0) direct = to_string(Wind::direction) + " stopni polnocny-wschod";
	if (Wind::direction > -180 && Wind::direction < -90) direct = to_string(Wind::direction) + " stopni polnocny-zachod";
	if (Wind::direction > 90 && Wind::direction < 180) direct = to_string(Wind::direction) + " stopni poludniowy-zachod";
	gText({ kamera.getCenter().x - 500, kamera.getCenter().y - 270 }, "Kierunek wiatru: " + direct);
	window->display();
}

void GraphicEngine::gFlight(MyPlane *plane)
{
	// Stworzenie kamery
	sf::View kamera(sf::Vector2f(640, 1800), sf::Vector2f(screenDimension.x, screenDimension.y));
	window->setView(kamera);
	// Aktualizacja kamery
	if (plane->position.y >= 1800)
		kamera.setCenter(plane->position.x, 1800);

	if (plane->position.y < 1800)
		kamera.setCenter(plane->position.x, plane->position.y);

	window->setView(kamera);
	myplaneSprite.setOrigin((plane->size.x) / 2, (plane->size.y) / 2);
	myplaneSprite.setPosition(plane->position);
	myplaneSprite.setRotation(plane->rotation);
	myplaneSprite.setScale(0.5, 0.7);

	myplane2Sprite.setOrigin((plane->size.x) / 2, (plane->size.y) / 2);
	myplane2Sprite.setPosition(plane->position);
	myplane2Sprite.setRotation(plane->rotation);
	myplane2Sprite.setScale(0.5, 0.7);

	myplane3Sprite.setOrigin((plane->size.x) / 2, (plane->size.y) / 2);
	myplane3Sprite.setPosition(plane->position);
	myplane3Sprite.setRotation(plane->rotation);
	myplane3Sprite.setScale(0.5, 0.7);

	myplane4Sprite.setOrigin((plane->size.x) / 2, (plane->size.y) / 2);
	myplane4Sprite.setPosition(plane->position);
	myplane4Sprite.setRotation(plane->rotation);
	myplane4Sprite.setScale(0.5, 0.7);

	worldSprite.setTexture(worldTexture);
	worldSprite.setTextureRect(sf::IntRect(0, 0, 2560, 2160));
	worldSprite.setPosition(0, 0);

	window->clear();
	window->draw(worldSprite);
	if (plane->position.y > 1850) window->draw(myplaneSprite);
	if (plane->position.y <= 1850 && plane->position.y > 1840) window->draw(myplane2Sprite);
	if (plane->position.y <= 1840 && plane->position.y > 1830) window->draw(myplane3Sprite);
	if (plane->position.y <= 1830) window->draw(myplane4Sprite);
	gText({ kamera.getCenter().x - 600, kamera.getCenter().y - 350 }, "Wysokosc: " + to_string(plane->height));
	gText({ kamera.getCenter().x - 600, kamera.getCenter().y - 330 }, "ASIR: " + to_string(plane->velocity));
	gText({ kamera.getCenter().x - 600, kamera.getCenter().y - 310 }, "GS: " + to_string(plane->v*3.6));
	gText({ kamera.getCenter().x - 600, kamera.getCenter().y - 270 }, "Stan paliwa: " + to_string((plane->fuel)));
	gText({ kamera.getCenter().x - 600, kamera.getCenter().y - 250 }, "Przebyty dystans: " + to_string((plane->distance)));
	gText({ kamera.getCenter().x - 600, kamera.getCenter().y - 290 }, "Predkosc wiatru: " + to_string((plane->windSpeed*3.6)));
	window->display();

}


