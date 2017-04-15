#include "Animation.h"

namespace CMaker {
	void Animation::Update(sf::Time _time)
	{
		Updatable::Update(_time);
		
		animationEngine.Update(_time);
	}

	Animation::Animation(CMaker::Texture _enumTexture, sf::Vector2f _pos):
		UpdatableUnit(_enumTexture,_pos),
		animationEngine(this)
	{

	}

	Animation::Animation():
		animationEngine(this)
	{
	}


	Animation::~Animation()
	{
	}

}