#pragma once
#include <TheCoffeeMaker/Transform.h>

namespace CMaker {

	class transLabel:
		public Transform
	{
	public:
		sf::Time			Apply(sf::Time _time, CMaker::SimpleAnimation* _entity) override;

		int					getLabel();

							transLabel(int _label);
							~transLabel();

	private:
		int					label;
	};

}