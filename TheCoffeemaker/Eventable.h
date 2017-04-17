#pragma once
#include <SFML/Window.hpp>

namespace CMaker {

	class Eventable
	{
	public:
		bool virtual	HandleInput(const sf::Event& _event) = 0;

						Eventable();
		virtual			~Eventable();
	};

}