#include "SimpleAnimation.h"

namespace CMaker {
	void SimpleAnimation::Update(sf::Time _time)
	{
		Updatable::Update(_time);

		animationEngine.Update(_time);
	}

	SimpleAnimation::SimpleAnimation(CMaker::Texture _enumTexture, sf::Vector2f _pos):
		AnimateEntity(_enumTexture,_pos),
		animationEngine(this)
	{

	}

	SimpleAnimation::SimpleAnimation():
		animationEngine(this)
	{
	}


	SimpleAnimation::~SimpleAnimation()
	{
	}

}