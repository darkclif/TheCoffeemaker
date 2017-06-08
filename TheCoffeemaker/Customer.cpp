#include "Customer.h"

#include <TheCoffeeMaker/AnimationFactory.h>

#include <TheCoffeemaker/ResourceManager.h>
#include <TheCoffeemaker/Console.h>

namespace CMaker {
	const sf::Time Customer::SAY_LENGTH = sf::seconds(10);

	void Customer::Update(sf::Time _time)
	{
		Animation::Update(_time);

		/* Customer logic */
		sayCurrLength += _time;

		if (sayCurrLength > Customer::SAY_LENGTH) {
			sayShow = false;
		}
	}

	void Customer::Draw(sf::RenderWindow & _render, sf::RenderStates _states)
	{
		Animation::Draw(_render, _states);

		if (sayShow) {
			_render.draw(entSay, _states);
		}
	}

	
	const std::vector<sf::IntRect> Customer::customersRect = {
		sf::IntRect(0,0,42,42),
		sf::IntRect(43,0,42,42),
		sf::IntRect(85,0,42,42),
	};

	Customer::Customer(sf::Vector2f _pos, int _cusId):
		Animation(CMaker::Texture::CUSTOMERS, _pos),
		sayShow{ true },
		pokes{ 0 },
		coffeeType{ (CoffeeType)(rand() % (int)CoffeeType::_SIZE) },
		coffeeExpectation{ CoffeeJudgeInst.getCoffeeComposition( coffeeType ) }
	{
		/* Create customer */
		this->setColorAlpha(0);
		this->setTextureRect(Customer::customersRect.at(_cusId));
		this->setScale(sf::Vector2f(4.f, 4.f));

		AnimationFactory::addAnimation<AnimationFactory::PredefAnimation::SLOW_SHOW>(1, &(this->animationEngine));
		this->animationEngine.runAnimation(1);

		/* Create say */
		this->entSay.setFillColor(sf::Color(212,139,53));
		this->entSay.setOutlineColor(sf::Color::Black);
		this->entSay.setOutlineThickness(1.f);
		this->entSay.setScale(sf::Vector2f(0.8f, 0.8f));
		this->entSay.setFont(ResourceMgr.getResource(CMaker::Font::DEFAULT));
		this->entSay.setPosition(_pos + sf::Vector2f(0.f, -50.f));
		this->entSay.setString(CoffeeJudge::CoffeeTypeToString.at((int)coffeeType));
	
		sayCurrLength = sf::Time::Zero;
	}

	Customer::~Customer()
	{

	}

	void Customer::eventPoke()
	{
		if (!sayShow) {
			sayCurrLength = sf::Time::Zero;
			sayShow = true;
			pokes++;
		}
	}

	void Customer::eventCoffeeConsume(const Coffee& _coffee)
	{
		C_DEBUG << "Consumed!" << std::endl;
	}

}