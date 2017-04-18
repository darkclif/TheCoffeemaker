#pragma once
#include <SFML/Graphics.hpp>

namespace CMaker {

	namespace Tools {
		/* Resize @rect1 making it contain @rect2 */
		void expandRect(sf::FloatRect& _rect1, sf::FloatRect& _rect2);

	}

}