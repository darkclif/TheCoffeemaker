#pragma once
#include <memory>

#include <TheCoffeeMaker/State.h>
#include <TheCoffeeMaker/Menu.h>

#include <TheCoffeeMaker/Cinamon.h>
#include <TheCoffeeMaker/SimpleAnimation.h>

namespace CMaker {

	class IntroState : public State
	{
	public:		
		void					HandleInput(const sf::Event& _event) override;
		void					Update(const sf::Time _time) override;
		void					Render() override;

		void					initEntities();

								IntroState(Game* _game);
								IntroState(Game* _game, bool _timeTrans, bool _rendTrans);
								~IntroState();
	
	private:
		/* Units */
		std::unique_ptr< CMaker::SimpleAnimation >	logoFoczkaEngine;
		std::unique_ptr< CMaker::SimpleAnimation >	logoTech;

		std::unique_ptr< CMaker::Menu >				menuTest;

		/* Events */
		void					endIntro();
	};

}