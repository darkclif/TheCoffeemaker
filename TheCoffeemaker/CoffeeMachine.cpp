#include "CoffeeMachine.h"

namespace CMaker {
	/* CONSTS */
	const sf::Time CoffeeMachine::TIME_PER_HEAT = sf::seconds(5);

	const sf::Vector2f CoffeeMachine::COFFEE_SMALL_POSTION = sf::Vector2f(0.f, -34.f);
	const sf::Vector2f CoffeeMachine::COFFEE_BIG_POSTION = sf::Vector2f(0.f, -40.f);

	void CoffeeMachine::Update(sf::Time _time)
	{
		if (attachedCoffee) {
			UpdatableUnit::Update(_time);

			if (getTime() >= TIME_PER_HEAT) {
				addTime(-TIME_PER_HEAT);
				attachedCoffee->addHeat(1);
				updateDoneBars();
			}
		}
	}

	/* Attached coffee managment */
	void CoffeeMachine::attachCoffee(Coffee * _coffee)
	{
		if (attachedCoffee) {
			attachedCoffee->detachFromMachine();
		}
		
		resetTime();
		attachedCoffee = _coffee;
		updateDoneBars();
	
		// Set coffee cup position 
		if (_coffee->getCoffeeType() == Coffee::CoffeeCupSize::BIG) {
			_coffee->setPosition(getPosition() + COFFEE_BIG_POSTION);
		}
		else {
			_coffee->setPosition(getPosition() + COFFEE_SMALL_POSTION);
		}
	}

	void CoffeeMachine::detachCoffee()
	{
		attachedCoffee = nullptr;
		updateDoneBars();
	}

	/* Constructor / Destructor */
	CoffeeMachine::CoffeeMachine(sf::Vector2f _pos):
		UpdatableUnit(Texture::COFFEE_MACHINE, _pos),
		attachedCoffee{nullptr},
		doneBars{0}
	{
		updateDoneBars();
		setOriginAlign(OriginAlign::BOTTOM_CENTER);
	}

	CoffeeMachine::~CoffeeMachine()
	{

	}

	void CoffeeMachine::updateDoneBars()
	{
		sf::Uint8 lBars;

		if (attachedCoffee) {
			lBars = (attachedCoffee->getHeat());
		}else{
			lBars = 0;
		}
		
		if (lBars >= MIN_DONE_BARS && lBars <= MAX_DONE_BARS) {
			doneBars = lBars;
			setMachineTextureRect();
		}
	}

	void CoffeeMachine::setMachineTextureRect()
	{
		static const sf::Vector2i machineRectSize(30, 42);

		static const std::vector<sf::IntRect> machineRects = {
			{ 0, 0, machineRectSize.x, machineRectSize.y },
			{ 30, 0, machineRectSize.x, machineRectSize.y },
			{ 60, 0, machineRectSize.x, machineRectSize.y },
			{ 90, 0, machineRectSize.x, machineRectSize.y },
			{ 120, 0, machineRectSize.x, machineRectSize.y },
			{ 150, 0, machineRectSize.x, machineRectSize.y },
		};

		setTextureRect(machineRects[doneBars]);
	}

}