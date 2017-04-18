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

	}

}