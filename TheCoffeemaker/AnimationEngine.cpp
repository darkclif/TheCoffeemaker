#include "AnimationEngine.h"
#include <TheCoffeeMaker/Console.h>
#include <TheCoffeeMaker/Transforms.h>

namespace CMaker {

	void AnimationEngine::Update(sf::Time _time)
	{
		if (!isRunning() || mapAnimations.empty())
			return;

		addTime(_time);

		sf::Time timeAbove = _time; // Time passed to next transform
		while( timeAbove > sf::Time::Zero && isRunning()){
			// Current transform of current animation
			auto& currTransformObj = mapAnimations.at(currAnimation).at(currTransform);

			timeAbove = currTransformObj->Apply(timeAbove, entity);

			// Go to next if current transform consumed all time
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

	void AnimationEngine::goToTransform(int _label)
	{
		for (unsigned int i = 0; i < mapAnimations[currAnimation].size(); ++i) {
			CMaker::Transform* tmpTrans = mapAnimations[currAnimation][i].get();

			CMaker::transLabel* tmpTransLabel = dynamic_cast<transLabel*>(tmpTrans);
			if (tmpTransLabel != nullptr) {
				int tmpLabel = tmpTransLabel->getLabel();

				if (tmpLabel == _label) {
					currTransform = i;
					return;
				}
			}
		}

		C_DEBUG << S_ERROR << "Transform with given label not found. (" << _label << ")" << std::endl;
	}

	void AnimationEngine::addAnimation(int _animation)
	{
		mapAnimations[_animation] = std::vector< std::unique_ptr< CMaker::Transform > >();

		if (mapAnimations.size() == 1) {
			currAnimation = _animation;
		}
	}

	/*
		Add transformations
	*/
	void AnimationEngine::addTransform(int _animation, CMaker::Transform * _transform)
	{
		if (mapAnimations.find(_animation) == mapAnimations.end()) {
			throw new std::exception("No registered animation number passed to addTransform() in AnimationEngine.");
		}

		mapAnimations.at(_animation).push_back(std::unique_ptr<Transform>(_transform));
	}

	void AnimationEngine::addGoto(int _animation, int _label)
	{
		addTransform(_animation, new CMaker::transGoto(_label, this));
	}

	void AnimationEngine::addLabel(int _animation, int _label)
	{
		addTransform(_animation, new CMaker::transLabel(_label));
	}

	/*
		Start / Stop
	*/
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