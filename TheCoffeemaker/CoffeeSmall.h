#pragma once
#include <TheCoffeeMaker/Coffee.h>

namespace CMaker {

	class CoffeeSmall:
		public Coffee
	{
	public:

		/* Constructor / Destructor */
				CoffeeSmall(sf::Vector2f _pos);
				~CoffeeSmall();
	};

}