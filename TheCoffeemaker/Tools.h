#pragma once
#include <SFML/Graphics.hpp>

namespace CMaker {

	namespace Tools {
		/* Resize @rect1 making it contain @rect2 */
		void expandRect(sf::FloatRect& _rect1, sf::FloatRect& _rect2);

		/* Move render view */
		void moveView(sf::RenderWindow& _window, sf::Vector2f _vect);

		/* Draw rect */
		void drawRect(sf::FloatRect _rect, sf::RenderWindow& _render, sf::Color _color = sf::Color::Cyan);
	}

}