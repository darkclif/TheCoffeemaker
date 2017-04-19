#pragma once
#include <TheCoffeeMaker/Menu.h>

namespace CMaker {
	class Game;

	class MainMenu:
		public Menu
	{
	public:

		/* Constructor / Destructor */
				MainMenu(Game* _game);
				~MainMenu();
	};

}