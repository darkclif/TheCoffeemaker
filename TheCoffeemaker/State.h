#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <TheCoffeeMaker/Updatable.h>
#include <TheCoffeeMaker/Drawable.h>

#include <memory>
#include <set>

namespace CMaker {
	class Game;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;

		void virtual					HandleInput(const sf::Event& _event) = 0;
		void virtual					Update(const sf::Time _time);
		void virtual					Render();

		/*	
			Enque and deque drawable entity to draw in each frame
			
			Entity deques when it is not visible.
		*/
		void							enqueDrawable(Drawable* _entity);
		void							dequeDrawable(sf::Uint32 _globalId);

		/*	
			Enque and deque updatable entity to update in each frame

			Entity deques when it is stopped.
		*/
		void							enqueUpdatable(Updatable* _entity);
		void							dequeUpdatable(sf::Uint32 _globalId);

		/* Transparency accesors */
		bool							isTimeTrans();
		bool							isRendTrans();

		/* Constructor / Destructor */
										State(Game* _game);
										State(Game* _game, bool _timeTrans, bool _rendTrans);
		virtual							~State();

	protected:
		/* Game object accesor */
		Game*							getGame();

	private:
		/* Game object */
		Game*							game;

		/* How to order drawable entities by layers */
		struct drawableComp {
			bool operator() (const Drawable* d1, const Drawable* d2) const {
				return d1->getLayer() < d2->getLayer();
			}
		};

		/* Entities queues to make drawing and update automaticaly */
		std::vector<CMaker::Updatable*>						queueUpdatable;
		std::multiset<CMaker::Drawable*, drawableComp>		queueDrawable;

		/* Pass time to states below */
		bool							timeTrans; 

		/* Render states below */
		bool							rendTrans; 
	};

}