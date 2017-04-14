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
	void Updatable::setTime(sf::Time _time)
	{
		time = _time;
	}

	sf::Time Updatable::getTime()
	{
		return time;
	}

}