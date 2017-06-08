#include "GameLevelState.h"

#include <TheCoffeeMaker/Tools.h>

#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>

#include <TheCoffeeMaker/CoffeeSmall.h>
#include <TheCoffeeMaker/CoffeeBig.h>
#include <TheCoffeeMaker/CoffeeMachine.h>

#include <TheCoffeemaker/ResourceManager.h>

namespace CMaker {
	/* Manage state */
	void GameLevelState::HandleInput(const sf::Event & _event)
	{
		switch (_event.type) {
			/* On key pressed */
			case sf::Event::EventType::KeyPressed:
				switch (_event.key.code) {
					case sf::Keyboard::Escape: getGame()->getStateMachine().reqPushState(EnumState::PAUSE_GAME); break;
					default: break;
				}
				break;
			/* On cursor moved */
			case sf::Event::EventType::MouseMoved:
				onMouseMoved(_event);
				break;
			/* On cursor released */
			case sf::Event::EventType::MouseButtonReleased:
				switch (_event.mouseButton.button) {
					case sf::Mouse::Button::Left: onMouseLeftReleased(_event); break;
					default: break;
				}
				break;
			/* On cursor clicked */
			case sf::Event::EventType::MouseButtonPressed:
				switch (_event.mouseButton.button) {
					case sf::Mouse::Button::Left: onMouseLeftPressed(_event); break;
					default: break;
				}
				break;
			default: break;
		}
	}

	void GameLevelState::Update(const sf::Time _time)
	{
		State::Update(_time);

		Tools::removeIf<Coffee::UniqPtr>(entCoffeeList, [](Coffee::UniqPtr& _elem) { return _elem->isToDelete(); });
	}

	void GameLevelState::Render()
	{
		State::Render();

		this->getGame()->getRender().draw(txtPoints);
	}
	
	/* Initialization */
	void GameLevelState::initEntities()
	{
		/* Customers */
		entCustomers.resize(3);
		for (int i = 0; i < 3; i++) {
			entCustomers[i] = std::make_unique<CMaker::Customer>(sf::Vector2f(70.f + i*240.f, 100.f), i);
			entCustomers[i]->setLayer(1);
			entCustomers[i]->addDrawQueue(this);
			entCustomers[i]->addUpdateQueue(this);
		}
		
		/* Point text */
		this->txtPoints.setFillColor(sf::Color::Red);
		this->txtPoints.setOutlineColor(sf::Color::Black);
		this->txtPoints.setOutlineThickness(1.f);
		this->txtPoints.setFont(ResourceMgr.getResource(CMaker::Font::DEFAULT));
		this->txtPoints.setPosition(sf::Vector2f(730.f, 20.f));
		this->txtPoints.setString("0");

		/* Background */
		entBackground = std::make_unique<CMaker::Unit>(CMaker::Texture::BACKGROUND, sf::Vector2f(0.f, 0.f));
		entBackground->setLayer(0);
		entBackground->fitRenderView(getGame()->getRender());
		entBackground->addDrawQueue(this);

		/* Table */
		entTable = std::make_unique<CMaker::Unit>(CMaker::Texture::TABLE, sf::Vector2f(0.f, 250.f));
		entTable->setOriginAlign(OriginAlign::TOP_LEFT);
		entTable->setScale(sf::Vector2f(30.f,3.f));
		entTable->setLayer(2);
		entTable->addDrawQueue(this);

		/* Bin */
		entBin = std::make_unique<CMaker::Bin>(sf::Vector2f(30.f, 500.f));
		entBin->setLayer(3);
		entBin->addDrawQueue(this);

		/* Coffeestacks */
		entCoffeeStacks.push_back( std::make_unique<CMaker::CoffeeStack>(Coffee::CoffeeCupSize::BIG, sf::Vector2f(30.f, 460.f)) );
		entCoffeeStacks.back()->setLayer(3);
		entCoffeeStacks.back()->addDrawQueue(this);

		entCoffeeStacks.push_back(std::make_unique<CMaker::CoffeeStack>(Coffee::CoffeeCupSize::SMALL, sf::Vector2f(75.f, 460.f)));
		entCoffeeStacks.back()->setLayer(3);
		entCoffeeStacks.back()->addDrawQueue(this);

		 /* Coffee machine */
		entCoffeeMachine = std::make_unique<CMaker::CoffeeMachine>(sf::Vector2f(690.f, 460.f));
		entCoffeeMachine->setScale(sf::Vector2f(3.f, 3.f));
		entCoffeeMachine->setLayer(3);
		entCoffeeMachine->addDrawQueue(this);
		entCoffeeMachine->addUpdateQueue(this);
	}
	
	/* Events */
	void GameLevelState::onMouseLeftPressed(sf::Event _event)
	{
		sf::Vector2f pressPoint = getGame()->getRender().mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));

		// Something is dragged
		if (dragObject(pressPoint)){
			return;
		}

		// Check if any stack is clicked
		for (auto& lStack : entCoffeeStacks) {
			if (lStack->getGlobalBounds().contains(pressPoint)) {
				spawnCoffee(lStack->getCoffeeType(),pressPoint);
				return;
			}
		}

		// Check if customer is clicked
		for (auto& lCustomer : entCustomers) {
			if (lCustomer->getGlobalBounds().contains(pressPoint)) {
				lCustomer->eventPoke();
				return;
			}
		}

	}

	void GameLevelState::onMouseLeftReleased(sf::Event _event)
	{
		sf::Vector2f releasePoint = getGame()->getRender().mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));

		if (draggedObject) {
			// If released above bin
			if (entBin->getGlobalBounds().contains(releasePoint)) {
				draggedObject->setToDelete(true);
			}

			// If released above coffee machine
			if (entCoffeeMachine->getGlobalBounds().contains(releasePoint)) {
				dynamic_cast<Coffee*>(draggedObject)->attachToMachine(entCoffeeMachine.get());
			}

			// If released above customer
			for (auto& lCustomer : entCustomers) {
				if (lCustomer->getGlobalBounds().contains(releasePoint)) {
					Coffee* lCoffee = dynamic_cast<Coffee*>(draggedObject);
					lCustomer->eventCoffeeConsume(*lCoffee);
					lCoffee->setToDelete(true);
				}
			}
			
			draggedObject = nullptr;
		}
	}

	void GameLevelState::onMouseMoved(sf::Event _event)
	{
		sf::Vector2f dragPoint = getGame()->getRender().mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));

		// If bin should open 
		entBin->setOpen(entBin->getGlobalBounds().contains(dragPoint));
		
		// If something is dragged
		if (draggedObject) {
			draggedObject->setPosition(dragPoint);
		}
	}
	
	void GameLevelState::spawnCoffee(Coffee::CoffeeCupSize _type, sf::Vector2f _pos)
	{
		// Spawn new coffee
		Coffee* newCoffee;
		switch (_type) {
			case Coffee::CoffeeCupSize::BIG: newCoffee = new CoffeeBig(_pos); break;
			case Coffee::CoffeeCupSize::SMALL: newCoffee = new CoffeeSmall(_pos); break;
			default: throw std::exception("Coffee type not implemented!"); break;
		}
		
		newCoffee->setLayer(4);
		newCoffee->addDrawQueue(this);

		entCoffeeList.push_back(std::unique_ptr<Coffee>(newCoffee));

		// Attach coffee to drag
		// Something is dragged
		dragObject(_pos);
	}

	bool GameLevelState::dragObject(sf::Vector2f _pos)
	{
		for (auto& lCoffee : entCoffeeList) {
			if (lCoffee->getGlobalBounds().contains(_pos)) {
				lCoffee->detachFromMachine();
				draggedObject = lCoffee.get();
				return true;
			}
		}

		return false;
	}

	/* Constructor / Destructor */
	GameLevelState::GameLevelState(Game * _game):
		State(_game)
	{
		points = 0;
		initEntities();
	}
	
	GameLevelState::GameLevelState(Game * _game, bool _timeTrans, bool _rendTrans):
		State(_game, _timeTrans, _rendTrans)
	{
		initEntities();
	}
	
	GameLevelState::~GameLevelState()
	{
	}

}