#include "IntroState.h"

#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/ResourceManager.h>

#include <SFML/Graphics.hpp>

namespace CMaker {
	/*
		STATE MANAGMENT	
	*/
	void IntroState::HandleInput(const sf::Event & _event)
	{

	}

	void IntroState::Update(const sf::Time _time)
	{

	}

	void IntroState::Render()
	{
		sf::RenderWindow& render = getGame()->getRender();

		static sf::Text testTxt;

		testTxt.setFont(ResourceMgr.getResource(Font::DEFAULT));
		testTxt.setString("Hello Bubus!");
		testTxt.setPosition(sf::Vector2f(100.f, 100.f));

		render.draw(testTxt);
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
}