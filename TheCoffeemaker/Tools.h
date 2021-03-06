#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace CMaker {

	namespace Tools {
		/** DEBUG **/

		/* Draw simple rect (debug) */
		void drawRect(sf::FloatRect _rect, sf::RenderWindow& _render, sf::Color _color = sf::Color::Cyan);


		/** TOOLS **/

		/* Resize @rect1 making it contain @rect2 */
		void expandRect(sf::FloatRect& _rect1, sf::FloatRect& _rect2);

		/* Move render view */
		void moveView(sf::RenderWindow& _window, sf::Vector2f _vect);

		/* Remove element from vector if criteria true */
		template<typename T>
		void removeIf(std::vector<T>& _vect, std::function<bool(T&)> _func) {
			auto it = std::remove_if(_vect.begin(), _vect.end(), _func);

			if (it != _vect.end())
				_vect.erase(it);
		}

	}

}