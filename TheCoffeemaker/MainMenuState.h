#pragma once
#include <memory>

#include <TheCoffeeMaker/State.h>
#include <TheCoffeeMaker/Menu.h>

namespace CMaker {

	class MainMenuState:
		public State
	{
	public:
		void							HandleInput(const sf::Event& _event);
		void							Update(const sf::Time _time);
		void							Render();

		void							initEntities();

										MainMenuState(Game* _game);
										MainMenuState(Game* _game, bool _timeTrans, bool _rendTrans);
										~MainMenuState();

	private:
		/* Units */
		std::unique_ptr< CMaker::Menu >	menuMain;

		/* Events */
	};

}