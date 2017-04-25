#pragma once
#include <TheCoffeeMaker/Menu.h>

namespace CMaker {

	class PauseMenu:
		public Menu
	{
	public:
		
		/* Constructor / Destructor */
				PauseMenu(Game* _game);
				~PauseMenu();
	};

}