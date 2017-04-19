#include "IntroState.h"

#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>
#include <TheCoffeeMaker/ResourceManager.h>

#include <SFML/Graphics.hpp>

namespace CMaker {
	/*
		State managment	
	*/
	void IntroState::HandleInput(const sf::Event & _event)
	{
		switch (_event.type) {
			/* On key pressed */
			case sf::Event::EventType::KeyPressed: 
				this->endIntro(); 
				break;
			/* On mouse button pressed */
			case sf::Event::EventType::MouseButtonPressed:
				if (_event.mouseButton.button == sf::Mouse::Button::Left) {
					this->endIntro();
				}
				break;
			default: break;
		}
	}

	void IntroState::Update(const sf::Time _time)
	{
		// Update entities
		logoFoczkaEngine->Update(_time);
		logoTech->Update(_time);

		// End intro if all animations ended
		if (!logoFoczkaEngine->isRunning() && !logoTech->isRunning()) {
			this->endIntro();
		}
	}

	void IntroState::Render()
	{
		// Draw entities
		sf::RenderWindow& render = getGame()->getRender();

		logoFoczkaEngine->Draw(render);
		logoTech->Draw(render);
	}

	void IntroState::initEntities()
	{
		// Focza Engine logo
		logoFoczkaEngine = std::make_unique<CMaker::SimpleAnimation>(CMaker::Texture::FOCZKA_ENGINE_LOGO);
		logoFoczkaEngine->setColorAlpha(0);
		logoFoczkaEngine->setPosition(getGame()->getRender().getView().getCenter() - sf::Vector2f(0.f, 80.f));
		logoFoczkaEngine->setOriginAlign(CMaker::OriginAlign::MIDDLE_CENTER);
		logoFoczkaEngine->loadAnimation<CMaker::AnimationFactory::PredefAnimation::SHOW_FADE>();

		// Logo of technologies
		logoTech = std::make_unique<CMaker::SimpleAnimation>(CMaker::Texture::TECH_LOGOS);
		logoTech->setColorAlpha(0);
		logoTech->setPosition(getGame()->getRender().getView().getCenter() + sf::Vector2f(0.f, 120.f));
		logoTech->setOriginAlign(CMaker::OriginAlign::MIDDLE_CENTER);
		logoTech->loadAnimation<CMaker::AnimationFactory::PredefAnimation::SHOW_FADE>();
	}

	/*
		Events
	*/
	void IntroState::endIntro() {
		this->getGame()->getStateMachine().reqPopState();
		this->getGame()->getStateMachine().reqPushState(EnumState::MAIN_MENU);
	}

	/*
		Constructor / Destructor
	*/
	IntroState::IntroState(Game* _game): 
		State(_game)
	{
		initEntities();
	}

	IntroState::IntroState(Game* _game, bool _timeTrans, bool _rendTrans): 
		State(_game, _timeTrans, _rendTrans)
	{
		initEntities();
	}

	IntroState::~IntroState()
	{

	}
}