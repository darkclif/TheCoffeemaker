#include "transGoto.h"
#include <TheCoffeeMaker/AnimationEngine.h>

namespace CMaker {
	sf::Time transGoto::Apply(sf::Time _time, CMaker::SimpleAnimation * _entity)
	{
		engine->goToTransform(targetTransLabel);

		return _time;
	}
	transGoto::transGoto(int _label, CMaker::AnimationEngine * _engine):
		targetTransLabel{_label},
		engine{_engine}
	{
	}

	transGoto::~transGoto()
	{
	}

}