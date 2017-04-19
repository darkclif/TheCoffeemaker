#pragma once
#include <TheCoffeeMaker/Animation.h>

namespace CMaker {

	class Coffee:
		public Animation
	{
	public:
		enum class CoffeeType {
			SMALL,
			BIG
		};

		/* Manage heat */
		void			setHeat(sf::Uint8 _heat);
		sf::Uint8		getHeat();

		/* Constructor / Destructor */
						Coffee(CoffeeType _type, sf::Vector2f _pos);
						~Coffee();

	private:
		static const sf::Uint8	HEAT_LIMIT = 9;

		sf::Uint8				heat;
	};

}