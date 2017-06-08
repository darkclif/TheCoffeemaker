#pragma once

#include <TheCoffeeMaker/Unit.h>

namespace CMaker {

	class CoffeeCompositionView:
		public Unit
	{
	public:
		/* Manage heat */
		void					setHeat(sf::Uint8 _heat);

		/* Constructor / Destructor */
								CoffeeCompositionView(sf::Vector2f _pos);
								~CoffeeCompositionView();
	private:
		// std::stack<>

	};

}