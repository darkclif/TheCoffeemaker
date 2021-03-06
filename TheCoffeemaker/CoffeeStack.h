#pragma once
#include <TheCoffeeMaker/Unit.h>
#include <TheCoffeeMaker/Coffee.h>

namespace CMaker {

	class CoffeeStack:
		public Unit
	{
	public:
		/* Coffee size accesor */
		Coffee::CoffeeCupSize	getCoffeeType();

		/* Constructor / Destructor */
							CoffeeStack(Coffee::CoffeeCupSize _type, sf::Vector2f _pos);
							~CoffeeStack();

	private:
		/* Size of served coffee cup */
		Coffee::CoffeeCupSize	type;
	};

}