#pragma once
#include <SFML/Graphics.hpp>

namespace CMaker {

	class Drawable
	{
	public:
		void virtual		Draw(sf::RenderWindow& _render) = 0;

							Drawable();
							~Drawable();
	};

}