#include "StateMachine.h"

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <TheCoffeeMaker/IntroState.h>
#include <TheCoffeeMaker/MainMenuState.h>
#include <TheCoffeeMaker/GameLevelState.h>
#include <TheCoffeeMaker/PauseGameState.h>

#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/Tools.h>

namespace CMaker {

	void StateMachine::Run()
	{
		const sf::Int64 TICKS_PER_SECOND = 120;
		const sf::Time TICK_TIME = sf::seconds(1) / TICKS_PER_SECOND;

		sf::Clock currClock;
		sf::Time currTime;

		this->applyPendingChanges();
		this->beginClock.restart();

		sf::Event event;
		sf::RenderWindow& render = game->getRender();
		while (!stateStack.empty()) {
			
			// Handle input
			while (render.pollEvent(event)) {
				if (this->HandleGlobalInput(event)) {
					this->HandleStatesInput(event);
				}
			}
			
			// Update 
			while(currTime.asSeconds() >= TICK_TIME.asSeconds()) {
				currTime -= TICK_TIME;
				this->ticks++;

				this->UpdateStates(TICK_TIME);
			}

			// Render
			this->RenderStates();
			
			// Engine actions
			this->applyPendingChanges();

			currTime += currClock.restart();
		}
	}

	/*
		STATES STACK MANIPULATE
	*/
	void StateMachine::PushState(EnumState _state)
	{
		stateStack.push_back(stateFactory.at(_state)());
	}

	void StateMachine::PopState()
	{
		if(!stateStack.empty())
			stateStack.pop_back();
	}

	void StateMachine::StackClear()
	{
		stateStack.clear();
	}

	/*
		MACHINE DELAYED REQUEST 

		When somebody want to change machine stack 
		from update loop we must save this change 
		and execute it after all states update.
	*/
	void StateMachine::reqPushState(EnumState _state)
	{
		delayedChanges.push_back([this, _state]() -> void { PushState(_state); });
	}

	void StateMachine::reqPopState()
	{
		delayedChanges.push_back([this]() -> void { PopState(); });
	}

	void StateMachine::reqStackClear()
	{
		delayedChanges.push_back([this]() -> void { StackClear(); });
	}

	float StateMachine::getFps() const
	{
		return ((float)ticks/beginClock.getElapsedTime().asSeconds());
	}

	void StateMachine::applyPendingChanges()
	{
		for(auto& it : delayedChanges) {
			// Execute stored delayed action
			it();
		}

		delayedChanges.clear();
	}

	/*
		CONSTRUCTOR / DESTRUCTOR
	*/
	StateMachine::StateMachine(Game* _game) : game{ _game }, ticks{0}
	{
		RegisterStates();
	}

	StateMachine::~StateMachine()
	{
	}

	/*
		STATES LOOP ACTIONS
	*/
	void StateMachine::UpdateStates(sf::Time _delta)
	{
		for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it) {
			(*it)->Update(_delta);

			if (!(*it)->isTimeTrans()) {
				break;
			}
		}
	}

	void StateMachine::RenderStates()
	{
		sf::RenderWindow& render = game->getRender();
		render.clear();

		// Find first non transparent from the top
		auto lowest_i = 0;
		for (unsigned int i = stateStack.size() - 1; i >= 0; --i) {

			if (!stateStack[i]->isRendTrans()) {
				lowest_i = i;
				break;
			}
		}

		// Render states from lowest to top
		for (unsigned int i = lowest_i; i < stateStack.size(); ++i) {
			stateStack[i]->Render();
		}

		render.display();
	}

	void StateMachine::HandleStatesInput(sf::Event& _event)
	{
		if (!stateStack.empty()) {
			stateStack.back()->HandleInput(_event);
		}
	}

	/*
		HANDLE MACHINE
	*/
	void StateMachine::RegisterStates()
	{
		registerState<CMaker::IntroState>(EnumState::INTRO);
		registerState<CMaker::MainMenuState>(EnumState::MAIN_MENU);
		registerState<CMaker::GameLevelState>(EnumState::GAME_LEVEL);
		registerState<CMaker::PauseGameState>(EnumState::PAUSE_GAME);
	}

	bool StateMachine::HandleGlobalInput(sf::Event& _event)
	{
		switch (_event.type) {
			/* Closed */
			case sf::Event::EventType::Closed: onClose(_event); break;

			/* Resized */
			case sf::Event::EventType::Resized: onResize(_event); break;

			/* Keys */
			case sf::Event::EventType::KeyPressed:
				switch (_event.key.code) {
					// DEBUG
					case sf::Keyboard::A: Tools::moveView(game->getRender(), sf::Vector2f(-10.f, 0.f)); break;
					case sf::Keyboard::D: Tools::moveView(game->getRender(), sf::Vector2f(10.f, 0.f)); break;
					case sf::Keyboard::W: Tools::moveView(game->getRender(), sf::Vector2f(0.f, -10.f)); break;
					case sf::Keyboard::S: Tools::moveView(game->getRender(), sf::Vector2f(0.f, 10.f)); break;
					default: break;
				}
				break;
			default: break;
		}

		return true;
	}

	/*
		EVENTS
	*/
	bool StateMachine::onClose(sf::Event& _event) {
		this->reqStackClear();

		return false;
	}

	void StateMachine::onResize(sf::Event _event) {
		// Fit render window to screen
		sf::Vector2f lBasicViewSize = game->getRender().getDefaultView().getSize();
		
		double h_ratio = (double)_event.size.height / (double)lBasicViewSize.y;
		double w_ratio = (double)_event.size.width / (double)lBasicViewSize.x;

		sf::View lView = game->getRender().getView();

		if (h_ratio < w_ratio) {
			double lWidthRatio = (h_ratio / w_ratio);
			double lWidthOffset = (1.f - lWidthRatio) / 2.f;
			lView.setViewport(sf::FloatRect((float)lWidthOffset, 0.f, (float)lWidthRatio, 1.f));
		}
		else {
			double lHeightRatio = (w_ratio / h_ratio);
			double lHeightOffset = (1.f - lHeightRatio) / 2.f;
			lView.setViewport(sf::FloatRect(0.f, (float)lHeightOffset, 1.f, (float)lHeightRatio));
		}

		game->getRender().setView(lView);
	}
}