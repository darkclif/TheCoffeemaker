#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transWait:
		public Transform
	{
	public:
		sf::Time		Apply(sf::Time _time, CMaker::SimpleAnimation* _entity) override;


						transWait(sf::Time _length);
						~transWait();
	};

}