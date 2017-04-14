#include "AnimationEngine.h"

namespace CMaker {
	void AnimationEngine::Update(sf::Time _time)
	{
		addTime(_time);
	}

	/*
		Constructor / Destructor
	*/
	AnimationEngine::AnimationEngine(CMaker::SimpleAnimation* _entity): 
		entity{ _entity }
	{

	}
	
	AnimationEngine::~AnimationEngine()
	{
	}
}