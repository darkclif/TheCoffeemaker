#pragma once
#include <TheCoffeeMaker/State.h>

namespace CMaker {

	class IntroState : public State
	{
	public:		
		void HandleInput(const sf::Event& _event);
		void Update(const sf::Time _time);
		void Render();

		IntroState(Game* _game);
		IntroState(Game* _game, bool _timeTrans, bool _rendTrans);
		~IntroState();

	};

}