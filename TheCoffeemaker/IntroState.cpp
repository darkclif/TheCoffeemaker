#include "IntroState.h"

#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>
#include <TheCoffeeMaker/ResourceManager.h>

#include <SFML/Graphics.hpp>

namespace CMaker {
	/*
		STATE MANAGMENT	
	*/
	void IntroState::HandleInput(const sf::Event & _event)
	{
		switch (_event.type) {
			/* On any key pressed */
			case sf::Event::EventType::KeyPressed: this->endIntro(_event); break;
			default: break;
		}
	}

	void IntroState::Update(const sf::Time _time)
	{
		cupCinamon->Update(_time);
	}

	void IntroState::Render()
	{
		sf::RenderWindow& render = getGame()->getRender();

		cupCinamon->Draw(render);
	}

	/*
		Constructor / Destructor
	*/
	IntroState::IntroState(Game* _game) : State(_game)
	{
		cupCinamon = std::make_unique<CMaker::Cinamon>(sf::Vector2f(100.f, 100.f));
	}

	IntroState::IntroState(Game* _game, bool _timeTrans, bool _rendTrans): 
		State(_game, _timeTrans, _rendTrans)
	{

	}

	IntroState::~IntroState()
	{

	}

	/*
		Events
	*/
	void IntroState::endIntro(const sf::Event&) {
		this->getGame()->getStateMachine().reqPopState();
		this->getGame()->getStateMachine().reqPushState(EnumState::INTRO);
	}
}