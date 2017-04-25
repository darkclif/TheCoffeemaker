#pragma once
#include <TheCoffeeMaker/Unit.h>

namespace CMaker {

	class Bin:
		public Unit
	{
	public:
		/* Open and close bin */
		void			setOpen(bool _open);

		/* Constructor / Destructor */
						Bin(sf::Vector2f _pos);
						~Bin();
	private:
		/* Set bin texture rect */
		void			setBinRect();

		/* If bin is open */
		bool			open;
	};

}