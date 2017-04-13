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

	}

	void IntroState::Render()
	{
		sf::RenderWindow& render = getGame()->getRender();

		sf::Text testTxt;

		testTxt.setFont(ResourceMgr.getResource(Font::DEFAULT));
		testTxt.setString("Hello Bubus!");
		testTxt.setPosition(sf::Vector2f(100.f, 100.f));

		sf::Sprite testSprite;

		testSprite.setTexture(ResourceMgr.getResource(Texture::SMALL_LOGO));
		testSprite.setPosition(sf::Vector2f(100.f, 300.f));
		testSprite.setScale(0.5f, 0.5f);

		render.draw(testTxt);
		render.draw(testSprite);
	}

	/*
		CONSTRUCTOR / DESTRUCTOR
	*/
	IntroState::IntroState(Game* _game) : State(_game){
	
	}

	IntroState::IntroState(Game* _game, bool _timeTrans, bool _rendTrans) : State(_game, _timeTrans, _rendTrans){

	}

	IntroState::~IntroState()
	{

	}

	/*
		EVENTS
	*/
	void IntroState::endIntro(const sf::Event&) {
		this->getGame()->getStateMachine().reqPopState();
		this->getGame()->getStateMachine().reqPushState(EnumState::INTRO);
	}
}