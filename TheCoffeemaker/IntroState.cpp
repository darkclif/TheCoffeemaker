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
		logoFoczkaEngine->Update(_time);
		logoTech->Update(_time);
	}

	void IntroState::Render()
	{
		sf::RenderWindow& render = getGame()->getRender();

		logoFoczkaEngine->Draw(render);
		logoTech->Draw(render);
	}

	/*
		Constructor / Destructor
	*/
	IntroState::IntroState(Game* _game) : State(_game)
	{
		logoFoczkaEngine = std::make_unique<CMaker::SimpleAnimation>(CMaker::Texture::FOCZKA_ENGINE_LOGO);
		logoFoczkaEngine->setColorAlpha(0);
		logoFoczkaEngine->setPosition(getGame()->getRender().getView().getCenter() - sf::Vector2f(0.f, 80.f));
		logoFoczkaEngine->setOriginAlign(CMaker::OriginAlign::MIDDLE_CENTER);
		logoFoczkaEngine->loadAnimation<CMaker::AnimationFactory::PredefAnimation::SHOW_FADE>();

		logoTech = std::make_unique<CMaker::SimpleAnimation>(CMaker::Texture::TECH_LOGOS);
		logoTech->setColorAlpha(0);
		logoTech->setPosition(getGame()->getRender().getView().getCenter() + sf::Vector2f(0.f, 120.f));
		logoTech->setOriginAlign(CMaker::OriginAlign::MIDDLE_CENTER);
		logoTech->loadAnimation<CMaker::AnimationFactory::PredefAnimation::SHOW_FADE>();
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