#include "Menu.h"
#include "Console.h"

#include <TheCoffeeMaker/Tools.h>

#include <TheCoffeeMaker/PageEntry.h>
#include <TheCoffeeMaker/MenuPage.h>

namespace CMaker {
	/*
		Update
	*/
	bool Menu::HandleInput(const sf::Event & _event)
	{
		// There is no pages in menu
		if (stackPages.empty()) {
			return true;
		}

		switch (_event.type) {
			/* On key pressed */
			case sf::Event::EventType::KeyPressed: 
				switch (_event.key.code){
					/* Default behavior */
					case sf::Keyboard::Up: getCurrentPage().Trigger(EntryAction::PREV_ENTRY); break;
					case sf::Keyboard::Down: getCurrentPage().Trigger(EntryAction::NEXT_ENTRY); break;

					/* My defined actions */
					case sf::Keyboard::Return: getCurrentPage().Trigger(EntryAction::SELECTED); break;
					case sf::Keyboard::Left: getCurrentPage().Trigger(EntryAction::ARROW_LEFT); break;
					case sf::Keyboard::Right: getCurrentPage().Trigger(EntryAction::ARROW_RIGHT); break;
					default: break;
				}
				break;
			/* On cursor moved */
			case sf::Event::EventType::MouseMoved:
				checkMouseMove(_event);
				break;
			/* On cursor clicked */
			case sf::Event::EventType::MouseButtonPressed:
				switch (_event.mouseButton.button) {
					case sf::Mouse::Button::Left: 
						checkMouseClick(_event);
						break;
					default: break;
				}
				break;
			default: break;
		}

		return false;
	}

	/*
		Draw
	*/
	void Menu::Draw(sf::RenderWindow & _render, sf::RenderStates _states)
	{
		if (!pagesBuilded) {
			buildPages();
		}

		_states.transform *= getTransform();
		mapMenuPages.at(stackPages.top())->Draw(_render, _states);
	}
	
	void Menu::buildPages()
	{
		int lPageNum = 0;
		for (auto& lPage : mapMenuPages) {
			(lPage.second)->buildPage(getTransform());

			if (lPageNum == 0) {
				menuArea = (lPage.second)->getPageArea();
			}
			else {
				Tools::expandRect(menuArea, (lPage.second)->getPageArea());
			}

			lPageNum++;
		}

		pagesBuilded = true;
	}

	/* 
		Add page and entries 
	*/
	void Menu::addPage(sf::Uint32 _pageNum, std::string _header)
	{
		if (mapMenuPages.find(_pageNum) != mapMenuPages.end()) {
			C_DEBUG << S_WARNING << "You are trying to add currently existing page to menu." << std::endl;
		}

		mapMenuPages.insert(std::make_pair(_pageNum, std::make_unique<MenuPage>(_header, menuStyle)));

		if (stackPages.empty()) {
			pushPage(_pageNum);
		}
	}

	void Menu::addEntry(sf::Uint32 _pageNum, std::string _name)
	{
		if (mapMenuPages.find(_pageNum) == mapMenuPages.end()) {
			C_DEBUG << S_WARNING << "You are trying to add entry to non existing page." << std::endl;
		}

		mapMenuPages.at(_pageNum)->addEntry(_name);
	}

	void Menu::setStartingPage(sf::Uint32 _page)
	{
		// Check if _page exist
		if (mapMenuPages.find(_page) == mapMenuPages.end()) {
			throw std::exception("No existing page passed as starting to Menu class.");
		}

		// Reset stack and push passed page
		while (!stackPages.empty()) 
			stackPages.pop();

		stackPages.push(_page);
	}

	/* Entry functions */
	void Menu::addEventFunction(sf::Uint32 _page, EntryAction _action, std::function<void()> _func)
	{
		auto& lPage = mapMenuPages.at(_page);
		lPage->addEntryTrigger(_action, _func);
	}

	void Menu::addEventFunctionPush(sf::Uint32 _page, EntryAction _action, int _targerPage)
	{
		// Add function
		auto& lPage = mapMenuPages.at(_page); 
		lPage->addEntryTrigger(_action, std::bind(&Menu::pushPage, this, _targerPage));
	}

	void Menu::addEventFunctionPop(sf::Uint32 _page, EntryAction _action)
	{
		auto& lPage = mapMenuPages.at(_page); 
		lPage->addEntryTrigger(_action, std::bind(&Menu::popPage, this));
	}

	/* Pages stack */
	void Menu::pushPage(int _targetPage)
	{
		stackPages.push(_targetPage);
	}

	void Menu::popPage()
	{
		if (stackPages.size() != 1)
			stackPages.pop();
	}

	Game * Menu::getGame()
	{
		return game;
	}

	MenuPage & Menu::getCurrentPage()
	{
		return *( mapMenuPages.at(stackPages.top()) );
	}

	/* Mouse events */
	void Menu::checkMouseMove(sf::Event _event)
	{
		auto& lRender = game->getRender();
		sf::Vector2f lMousePoint = lRender.mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));

		lMousePoint = getInverseTransform().transformPoint(lMousePoint);

		getCurrentPage().checkMouseHighlight(lMousePoint);
	}

	void Menu::checkMouseClick(sf::Event _event)
	{
		auto& lRender = game->getRender();
		sf::Vector2f lMousePoint = lRender.mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));

		lMousePoint = getInverseTransform().transformPoint(lMousePoint);

		getCurrentPage().checkMouseClick(lMousePoint);
		getCurrentPage().checkMouseHighlight(lMousePoint);
	}

	/*
		Constructor / Destructor 
	*/
	Menu::Menu(Game* _game) :
		game{ _game },
		pagesBuilded{false}
	{
	}

	Menu::~Menu()
	{
	}

}