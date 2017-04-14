#include "Updatable.h"

namespace CMaker {

	/* Update time */
	void Updatable::Update(sf::Time _time)
	{
		addTime(_time);
	}

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