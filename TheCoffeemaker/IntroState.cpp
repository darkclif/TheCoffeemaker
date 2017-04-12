#include "IntroState.h"

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