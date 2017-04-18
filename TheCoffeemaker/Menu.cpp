#include "Menu.h"
#include "Console.h"

#include <TheCoffeeMaker/Tools.h>

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
					// Default behavior
					case sf::Keyboard::Up: changeEntry(-1); break;
					case sf::Keyboard::Down: changeEntry(1); break;

					/* My defined actions */
					case sf::Keyboard::Return: triggerCurrentEntry(Entry::Action::SELECTED); break;
					default: break;
				}
				break;
			/* On cursor moved */
			case sf::Event::EventType::MouseMoved:
				checkEntryHighlight(_event);
				break;
			/* On cursor clicked */
			case sf::Event::EventType::MouseButtonPressed:
				switch (_event.mouseButton.button) {
					case sf::Mouse::Button::Left: checkMouseClick(_event); break;
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
	void Menu::Draw(sf::RenderWindow & _render)
	{
		sf::Color normColor(255, 255, 255); // Color of not selected entry
		sf::Color currColor(225, 23, 23); // Color of selected entry

		if (!menuBuilded) {
			buildMenu();
		}

		PageInfo lCurrPage = getCurrentPageInfo();
		std::vector<Entry>& lEntries = mapMenuPages.at(lCurrPage.page);

		// DEBUG
		sf::RectangleShape menuRect;
		menuRect.setPosition(sf::Vector2f(menuArea.left, menuArea.top));
		menuRect.setSize(sf::Vector2f(menuArea.width, menuArea.height));
		menuRect.setFillColor(sf::Color::Cyan);
		_render.draw(menuRect);

		for (unsigned int i = 0; i < lEntries.size(); ++i) {
			Entry& lEntry = lEntries[i];

			// DEBUG
			sf::FloatRect rect = lEntry.text.getGlobalBounds();
			sf::RectangleShape textRect;
			textRect.setPosition(sf::Vector2f(rect.left, rect.top));
			textRect.setSize(sf::Vector2f(rect.width, rect.height));
			textRect.setFillColor(sf::Color::Blue);
			_render.draw(textRect);

			lEntry.text.setFillColor(i == lCurrPage.entry ? currColor : normColor);
			_render.draw(lEntry.text);
		}
	}
	
	void Menu::buildMenu()
	{
		sf::Color normColor(255, 255, 255); // Color of not selected entry
		sf::Color currColor(225, 23, 23); // Color of selected entry

		sf::Vector2f startPosition(100.f, 100.f);
		sf::Vector2f deltaMove(0.f, 50.f); // Space between entries
		bool firstTextBox = true;

		sf::Text lText;
		lText.setFont(ResourceMgr.getResource(font));

		for (auto& lPage : mapMenuPages) {
			auto& lEntries = lPage.second;
			lText.setPosition(100.f, 100.f);

			for (unsigned int i = 0; i < lEntries.size(); ++i) {
				Entry& lEntry = lEntries[i];

				lText.setString(lEntry.name);
				lText.move(deltaMove);

				// Expand menu area
				sf::FloatRect lTextArea = lText.getGlobalBounds();
				if (firstTextBox) {
					menuArea = lTextArea;
					firstTextBox = false;
				}
				else {
					Tools::expandRect(menuArea, lTextArea);
				}

				lEntry.text = lText;
			}
		}

		menuBuilded = true;
	}

	void Menu::addPage(int _page)
	{
		if (mapMenuPages.find(_page) != mapMenuPages.end()) {
			C_DEBUG << S_WARNING << "You are trying to add currently existing page to menu." << std::endl;
		}

		mapMenuPages.insert(std::make_pair(_page, std::vector<Entry>()));
	}

	void Menu::addEntry(int _page, std::string _name)
	{
		if (mapMenuPages.find(_page) == mapMenuPages.end()) {
			throw std::exception("You are trying to add entry to non existing page in menu.");
		}

		mapMenuPages.at(_page).push_back(Entry(_name));

		// This is first entry so push it on stack
		if (stackPages.empty()) {
			setStartingPage(_page, 0);
		}
	}

	void Menu::setStartingPage(int _page, unsigned int _entry)
	{
		// Check if _page and _entry exist
		auto tmpPage = mapMenuPages.find(_page);
		if (tmpPage == mapMenuPages.end()) {
			throw std::exception("No existing page passed as starting to Menu class.");
		}

		if (_entry >= tmpPage->second.size()) {
			throw std::exception("No existing page entry passed as starting to Menu class.");
		}

		// Reset stack and push passed page and entry
		while (!stackPages.empty()) 
			stackPages.pop();

		stackPages.push(PageInfo(_page, _entry));
	}

	/* Entry functions */
	void Menu::addEventFunction(int _page, Entry::Action _action, std::function<void()> _func)
	{
		// Add function
		auto& lEntry = getPageLastEntry(_page);
		lEntry.actFunctions.insert(std::make_pair(_action, _func));
	}

	void Menu::addEventFunctionPush(int _page, Entry::Action _action, int _targerPage)
	{
		// Add function
		auto& lEntry = getPageLastEntry(_page); 
		lEntry.actFunctions.insert(std::make_pair(_action, std::bind(&Menu::pushPage, this, _targerPage)));
	}

	void Menu::addEventFunctionPop(int _page, Entry::Action _action)
	{
		// Add function
		auto& lEntry = getPageLastEntry(_page);
		lEntry.actFunctions.insert(std::make_pair(_action, std::bind(&Menu::popPage, this)));
	}

	void Menu::pushPage(int _targetPage)
	{
		stackPages.push(PageInfo(_targetPage, 0));
	}

	void Menu::popPage()
	{
		if (stackPages.size() != 1)
			stackPages.pop();
	}

	void Menu::setFont(CMaker::Font _font)
	{
		font = _font;
	}

	void Menu::triggerCurrentEntry(Entry::Action _action)
	{
		getCurrentEntry().Trigger(_action);
	}

	void Menu::checkEntryHighlight(sf::Event _event)
	{
		auto& lRender = game->getRender();
		sf::Vector2f lMousePoint = lRender.mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));

		// Not in menu area
		if (!menuArea.contains(lMousePoint))
			return;

		// Check all entries of current page
		PageInfo& currPage = getCurrentPageInfo();
		auto& currEntries = mapMenuPages.at(currPage.page);

		for (sf::Uint32 i = 0; i < currEntries.size(); ++i) {
			auto& lEntry = currEntries[i];
			if (lEntry.text.getGlobalBounds().contains(lMousePoint)) {
				currPage.entry = i;
				lEntry.Trigger(Entry::Action::HIGHLIGHTED);
				return;
			}
		}
	}

	void Menu::checkMouseClick(sf::Event _event)
	{
		auto& lRender = game->getRender();
		sf::Vector2f lMousePoint = lRender.mapPixelToCoords(sf::Vector2i(_event.mouseButton.x, _event.mouseButton.y));

		// Check if current entry is clicked 
		auto& currEntry = getCurrentEntry();

		if (currEntry.text.getGlobalBounds().contains(lMousePoint)) {
			if (currEntry.Trigger(Entry::Action::SELECTED)) {
				// Menu page can be changed after selection 
				// so call mouse move event to check new 
				// highlighted entry.
				sf::Event newEvent;
				newEvent.type = sf::Event::EventType::MouseMoved;
				newEvent.mouseMove.x = _event.mouseButton.x;
				newEvent.mouseMove.y = _event.mouseButton.y;

				checkEntryHighlight(newEvent);
			};
		}
	}

	Menu::Entry & Menu::getCurrentEntry()
	{
		PageInfo lCurrPageInfo = getCurrentPageInfo();
		auto& lCurrPage = mapMenuPages.at(lCurrPageInfo.page);
		return lCurrPage.at(lCurrPageInfo.entry);
	}

	Menu::PageInfo& Menu::getCurrentPageInfo()
	{
		if (stackPages.empty())
			throw std::exception("You are trying to get current page when no page is on stack.");

		return stackPages.top();
	}

	Menu::Entry& Menu::getPageLastEntry(int _page)
	{
		// Check if _page and at last one _entry exist
		auto tmpPage = mapMenuPages.find(_page);
		if (tmpPage == mapMenuPages.end()) {
			throw std::exception("No existing page passed as starting to Menu class.");
		}

		if (tmpPage->second.empty()) {
			throw std::exception("There is no at last one entry in given menu page, cannot add a function.");
		}

		// Return last entry
		return tmpPage->second.back();
	}

	void Menu::changeEntry(int _change)
	{
		PageInfo currPage = getCurrentPageInfo();

		int currEntry = currPage.entry;
		currEntry += _change;
		currEntry %= mapMenuPages.at(currPage.page).size();

		stackPages.top().entry = currEntry;
	}

	/*
		Constructor / Destructor 
	*/
	Menu::Menu(Game* _game):
		font{ CMaker::Font::DEFAULT },
		menuBuilded{ false },
		game{ _game }
	{
	}

	Menu::~Menu()
	{
	}

}