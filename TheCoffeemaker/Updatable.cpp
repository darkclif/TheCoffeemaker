#include "Updatable.h"

namespace CMaker {

	/*
		Constructor / Destructor
	*/
	Updatable::Updatable()
	{

	}

	Updatable::~Updatable()
	{

	}

	/*
		Manage time
	*/
	void Updatable::addTime(sf::Time _time)
	{
		time += _time;
	}

	void Updatable::resetTime()
	{
		time = sf::Time();
	}

	sf::Time Updatable::getTime()
	{
		return time;
	}

}