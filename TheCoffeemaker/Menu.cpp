#include "Menu.h"
#include "Console.h"

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
				// Default behavior
				switch (_event.key.code){
					case sf::Keyboard::Up: changeEntry(-1); break;
					case sf::Keyboard::Down: changeEntry(1); break;
					default: break;
				}

				// Check current entry functions
				triggerCurrentEntry(_event.key.code);

				break;
			default: break;
		}

		return true;
	}

	/*
		Draw
	*/
	void Menu::Draw(sf::RenderWindow & _render)
	{
		sf::Color normColor(255,255,255); // Color of not selected entry
		sf::Color currColor(225, 23, 23); // Color of selected entry
		sf::Vector2f deltaMove(0.f, 50.f); // Space between entries

		sf::Text lText;
		lText.setFont(ResourceMgr.getResource(font));
		lText.setPosition(100.f, 100.f);

		PageInfo lCurrPage = getCurrentPageInfo();
		std::vector<Entry>& lEntries = mapMenuPages.at(lCurrPage.page);

		for (unsigned int i = 0; i < lEntries.size(); ++i) {
			Entry& lEntry = lEntries[i];

			lText.setString( lEntry.name );
			lText.move(deltaMove);
			lText.setFillColor(i==lCurrPage.entry ? currColor : normColor);

			_render.draw(lText);
		}
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
	void Menu::addEventFunction(int _page, sf::Keyboard::Key _key, std::function<void()> _func)
	{
		// Add function
		auto& lEntry = getPageLastEntry(_page);
		lEntry.actions.push_back(std::make_pair(_key, _func));
	}

	void Menu::addEventFunctionPush(int _page, sf::Keyboard::Key _key, int _targerPage)
	{
		// Add function
		auto& lEntry = getPageLastEntry(_page); 
		lEntry.actions.push_back(std::make_pair(_key, std::bind(&Menu::pushPage, this, _targerPage)));
	}

	void Menu::addEventFunctionPop(int _page, sf::Keyboard::Key _key)
	{
		// Add function
		auto& lEntry = getPageLastEntry(_page);
		lEntry.actions.push_back(std::make_pair(_key, std::bind(&Menu::popPage, this)));
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

	void Menu::triggerCurrentEntry(sf::Keyboard::Key _key)
	{
		// Get current entry
		PageInfo lCurrPageInfo = getCurrentPageInfo();
		auto& lCurrPage = mapMenuPages.at(lCurrPageInfo.page);
		auto& lCurrEntry = lCurrPage.at(lCurrPageInfo.entry);

		// Check if event is triggered
		for (auto& lEventFunc : lCurrEntry.actions) {
			if (lEventFunc.first == _key) {
				lEventFunc.second();
			}
		}
	}

	Menu::PageInfo Menu::getCurrentPageInfo()
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
	Menu::Menu():
		font{ CMaker::Font::DEFAULT }
	{
	}

	Menu::~Menu()
	{
	}

}