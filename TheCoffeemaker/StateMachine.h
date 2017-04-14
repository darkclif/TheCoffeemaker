#pragma once
#include <TheCoffeeMaker\State.h>

#include <stack>
#include <map>
#include <functional>
#include <memory>

namespace CMaker {

	enum class EnumState {
		INTRO,
		MENU,
		GAME
	};

	class StateMachine
	{
	public:
		void Run();

		void reqPushState(EnumState _state);
		void reqPopState();
		void reqStackClear();

		float getFps() const;

		StateMachine(Game* _game);
		~StateMachine();

	private:
		void PushState(EnumState _state);
		void PopState();
		void StackClear();

		void UpdateStates(sf::Time _delta);
		void HandleStatesInput(sf::Event& _event);
		void RenderStates();

		void applyPendingChanges();

		/**
			Handle global events
			@return True if you want to propagate catched event further. 
		*/
		bool HandleGlobalInput(sf::Event& _event);

		/**
			Register existing states in states factory
		*/
		void RegisterStates();

		template <typename S>
		void registerState(EnumState _state) {
			this->stateFactory[_state] = [this]() { return State::Ptr(new S(this->game)); };
		}

	private:
		/*	Global events functions 
			@return True if you want to pass event further.
		*/
		bool onClose(sf::Event& _event);

	private:
		std::map< EnumState, std::function<State::Ptr()> >	stateFactory;
		std::vector< std::unique_ptr<CMaker::State> >		stateStack;

		std::vector< std::function<void()> >				delayedChanges;
	
	private:
		CMaker::Game* game;

		long int	ticks;
		sf::Clock	beginClock;
	};

}