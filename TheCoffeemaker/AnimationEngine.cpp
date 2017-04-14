#include "AnimationEngine.h"
#include <TheCoffeeMaker/Console.h>

namespace CMaker {
	void AnimationEngine::Update(sf::Time _time)
	{
		if (!isRunning() || mapAnimations.empty())
			return;

		addTime(_time);

		sf::Time timeAbove = _time;
		while( timeAbove > sf::Time::Zero && isRunning()){
			auto& currTransformObj = mapAnimations.at(currAnimation).at(currTransform);

			timeAbove = currTransformObj->Apply(timeAbove, entity);

			if (timeAbove > sf::Time::Zero) {
				nextTransform();
			}
		};
	}

	void AnimationEngine::runAnimation(int _animation)
	{
		if (mapAnimations.find(_animation) != mapAnimations.end()) {
			currAnimation = _animation;
			currTransform = 0;
		}
		else {
			C_DEBUG << S_ERROR << "No registered animation number passed to runAnimation() in AnimationEngine." << std::endl;
		}
	}

	void AnimationEngine::nextTransform()
	{
		currTransform++;

		if (currTransform >= mapAnimations[currAnimation].size()) {
			currTransform = 0;
			setRunning(false);
		}
	}

	void AnimationEngine::addAnimation(int _animation)
	{
		mapAnimations[_animation] = std::vector< std::unique_ptr< CMaker::Transform > >();

		if (mapAnimations.size() == 1) {
			currAnimation = _animation;
		}
	}

	void AnimationEngine::addTransform(int _animation, CMaker::Transform * _transform)
	{
		if (mapAnimations.find(_animation) == mapAnimations.end()) {
			throw new std::exception("No registered animation number passed to addTransform() in AnimationEngine.");
		}

		mapAnimations.at(_animation).push_back(std::unique_ptr<Transform>(_transform));
	}

	bool AnimationEngine::isRunning()
	{
		return running;
	}

	void AnimationEngine::setRunning(bool _running)
	{
		running = _running;
	}

	/*
		Constructor / Destructor
	*/
	AnimationEngine::AnimationEngine(CMaker::SimpleAnimation* _entity): 
		entity{ _entity },
		running{ true },
		currAnimation{ 0 },
		currTransform{ 0 }
	{
	}
	
	AnimationEngine::~AnimationEngine()
	{
	}

}