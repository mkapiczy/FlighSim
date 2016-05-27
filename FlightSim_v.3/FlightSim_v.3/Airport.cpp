/**
* \file	Airport.cpp
* \brief Plik Ÿród³owy klasy Airport
*/

#include "stdafx.h"
#include "Airport.h"


Airport::Airport()
{
	front = NULL;
	back = NULL;
	count = 0;
	nPlanes = 2;
}

Airport::~Airport()
{
	Vehicle *temp;
	while (front != NULL){
		temp = front;
		front = front->next;
		delete temp;
	}
}

void Airport::addPlane(Plane *plane)
{
	Plane *nowy = new Plane(plane->id, { plane->position.x, plane->position.y });
	nowy->position.x = plane->position.x;
	nowy->position.y = plane->position.y;
	nowy->next = NULL;

	Plane *temp;
	temp = front;

	if (temp==NULL)
	{
		front = nowy;
	}
	else if (temp!=NULL)
	{
		while (temp->next) temp = temp->next;
		temp->next = nowy;
	}

	back = front;
	while (back->next) back = back->next;

	count++;
	nPlanes++;
}

void Airport::removePlane()
{
	Plane *temp;
	temp = front;
	if (temp){
		front = temp->next;
		delete temp;
		count--;
	}
}

void Airport::clear()
{
	Plane *temp;

	if (front != NULL)
	{
		while (front != NULL)
		{
			temp = front;
			front = front->next;
			delete temp;
		}
	}
	count = 0;

}

void Airport::show()
{
	Plane *temp;
	temp = front;
	cout << endl << " ***** STAN LOTNISKA ***** " << endl << endl;
	int i = 1;
	if (temp)
	{
		cout << "----------------------" << endl;
		cout << i << ": " << "Samolot nr: " << temp->id << endl;
		i++;
		while (temp->next)
		{
			temp = temp->next;
			cout << "----------------------" << endl;
			cout << i << ": " << "Samolot nr: " << temp->id << endl;
			i++;
		}
	}
	else cout << "PUSTE" << endl;
}

void Airport::refuse()
{
	cout << "Nie ma pozwolenia na ladowanie. Lotnisko pelne!" << endl;
}

bool Airport::full()
{
	if (count < Airport::MAX_CAPACITY)
		return false;
	else 
		return true;
}

bool Airport::empty()
{
	if (count == 0)
		return true;
	else
		return false;
}

bool Airport::runaway()
{
	if (count == 0)	return true;
	else return false;
}


void Airport::land(Vehicle *plane)
{
	cout << "Samolot " << plane->id << " wyladowal" << endl;
}

void Airport::depart(Vehicle *plane)
{
	cout << "Samolot " << plane->id << " wylecial" << endl;
}

void Airport::addBus(Bus *bus)
{
	Bus *nowy = new Bus(bus->id, { bus->position.x, bus->position.y });
	nowy->position.x = bus->position.x;
	nowy->position.y = bus->position.y;
	nowy->next = NULL;

	Bus *temp;
	temp = busfront;

	if (temp == NULL)
	{
		busfront = nowy;
	}
	else if (temp != NULL)
	{
		while (temp->next) temp = temp->next;
		temp->next = nowy;
	}

	busback = busfront;
	while (busback->next) busback = busback->next;

	count++;
}

void Airport::removeBus()
{
	Bus *temp;
	temp = busfront;
	if (temp){
		busfront = temp->next;
		delete temp;
		count--;
	}
}

void Airport::clearbus()
{
	Bus *temp;

	if (busfront != NULL)
	{
		while (busfront != NULL)
		{
			temp = busfront;
			busfront = busfront->next;
			delete temp;
		}
	}
	count = 0;
}