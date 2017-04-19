#include "GameLevelState.h"

#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/CoffeeSmall.h>
#include <TheCoffeeMaker/CoffeeBig.h>

namespace CMaker {
	/* Manage state */
	void GameLevelState::HandleInput(const sf::Event & _event)
	{
		switch (_event.type) {
			/* On key pressed */
			case sf::Event::EventType::KeyPressed:
				switch (_event.key.code) {
					case sf::Keyboard::Up: break;
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
	}

	void GameLevelState::Render()
	{
		State::Render();
	}
	
	/* Initialization */
	void GameLevelState::initEntities()
	{
		/* Background */
		entBackground = std::make_unique<CMaker::Unit>(CMaker::Texture::BACKGROUND, sf::Vector2f(0.f, 0.f));
		entBackground->setLayer(1);
		entBackground->fitRenderView(getGame()->getRender());
		entBackground->addDrawQueue(this);

		/* Table */
		entTable = std::make_unique<CMaker::Unit>(CMaker::Texture::TABLE, sf::Vector2f(0.f, 250.f));
		entTable->setOriginAlign(OriginAlign::TOP_LEFT);
		entTable->setScale(sf::Vector2f(30.f,3.f));
		entTable->setLayer(2);
		entTable->addDrawQueue(this);

		/* Coffeestacks */
		entCoffeeStacks.push_back( std::make_unique<CMaker::CoffeeStack>(Coffee::CoffeeType::BIG, sf::Vector2f(30.f, 460.f)) );
		entCoffeeStacks.back()->setLayer(3);
		entCoffeeStacks.back()->addDrawQueue(this);

		entCoffeeStacks.push_back(std::make_unique<CMaker::CoffeeStack>(Coffee::CoffeeType::SMALL, sf::Vector2f(55.f, 467.f)));
		entCoffeeStacks.back()->setLayer(3);
		entCoffeeStacks.back()->addDrawQueue(this);

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
	}

	void GameLevelState::onMouseLeftReleased(sf::Event _event)
	{
		draggedObject = nullptr;
	}

	void GameLevelState::onMouseMoved(sf::Event _event)
	{
		// If something is dragged
		if (draggedObject) {
			sf::Vector2f dragPoint = getGame()->getRender().mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));
			draggedObject->setPosition(dragPoint);
		}
	}
	
	void GameLevelState::spawnCoffee(Coffee::CoffeeType _type, sf::Vector2f _pos)
	{
		// Spawn new coffee
		Coffee* newCoffee;
		switch (_type) {
			case Coffee::CoffeeType::BIG: newCoffee = new CoffeeBig(_pos); break;
			case Coffee::CoffeeType::SMALL: newCoffee = new CoffeeSmall(_pos); break;
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