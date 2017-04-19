#include "Tools.h"

namespace CMaker {

	namespace Tools {
		void expandRect(sf::FloatRect& _rect1, sf::FloatRect& _rect2)
		{
			if (_rect2.left < _rect1.left) {
				_rect1.width += (_rect1.left - _rect2.left);
				_rect1.left = _rect2.left;
			}

			if (_rect2.top < _rect1.top) {
				_rect1.height += (_rect1.top - _rect2.top);
				_rect1.top = _rect2.top;
			}

			if ((_rect2.left + _rect2.width) > (_rect1.left + _rect1.width)) {
				_rect1.width += ((_rect2.left + _rect2.width) - (_rect1.left + _rect1.width));
			}

			if ((_rect2.top + _rect2.height) > (_rect1.top + _rect1.height)) {
				_rect1.height += ((_rect2.top + _rect2.height) - (_rect1.top + _rect1.height));
			}
		}

		void moveView(sf::RenderWindow& _window, sf::Vector2f _vect) {
			sf::View lView = _window.getView();
			lView.setCenter(lView.getCenter() + _vect);
			_window.setView(lView);
		}

		void drawRect(sf::FloatRect _rect, sf::RenderWindow & _render, sf::Color _color)
		{
			sf::RectangleShape lRect;
			lRect.setPosition(sf::Vector2f(_rect.left, _rect.top));
			lRect.setSize(sf::Vector2f(_rect.width, _rect.height));
			lRect.setFillColor(_color);
			_render.draw(lRect);
		}

	}

}