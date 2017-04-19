#pragma once
#include <TheCoffeeMaker/Coffee.h>

namespace CMaker {

	class CoffeeBig:
		public Coffee
	{
	public:

		/* Constructor / Destructor */
				CoffeeBig(sf::Vector2f _pos);
				~CoffeeBig();
	};

}