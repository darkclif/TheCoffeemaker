#pragma once

#include <TheCoffeeMaker/Unit.h>

namespace CMaker {

	class HeatBar:
		public Unit
	{
	public:
		/* Manage heat */
		void					setHeat(sf::Uint8 _heat);

		/* Set texture rect for heat bar */
		void					setHeatRect();

		/* Constructor / Destructor */
								HeatBar(sf::Vector2f _pos, sf::Uint8 _heat = 1);
								~HeatBar();
	private:
		static const sf::Uint8	MAX_BARS = 9;
		sf::Uint8				heat;
	};

}