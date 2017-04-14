#pragma once

#include <SFML/System.hpp>

namespace CMaker {

	class Updatable
	{
	public:
		void virtual		Update(sf::Time _time) = 0;

							Updatable();
		virtual 			~Updatable();

	protected:
		void				addTime(sf::Time _time);
		void				resetTime();
		sf::Time			getTime();

	private:
		sf::Time			time;
	};

}