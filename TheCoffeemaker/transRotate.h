#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transRotate :
		public Transform
	{
	public:
		sf::Time			Apply(sf::Time _time, CMaker::Animation* _entity) override;

							transRotate(float _rotation, sf::Time _length);
							~transRotate();

	private:
		float				startRotation;
		float				targetRotation;
	};

}