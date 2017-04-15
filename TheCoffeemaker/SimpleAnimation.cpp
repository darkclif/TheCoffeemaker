#include "SimpleAnimation.h"

namespace CMaker {

	SimpleAnimation::SimpleAnimation(CMaker::Texture _enumTexture, sf::Vector2f _pos):
		Animation(_enumTexture,_pos)
	{
	}

	SimpleAnimation::SimpleAnimation(CMaker::Texture _enumTexture) :
		Animation(_enumTexture, sf::Vector2f())
	{
	}

	SimpleAnimation::SimpleAnimation()
	{
	}


	SimpleAnimation::~SimpleAnimation()
	{
	}

}