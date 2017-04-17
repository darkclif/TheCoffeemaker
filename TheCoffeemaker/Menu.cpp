#include "Menu.h"
#include "Console.h"

namespace CMaker {
	/*
		Update
	*/
	bool Menu::HandleInput(const sf::Event & _event)
	{
		switch (_event.type) {
			/* On key pressed */
			case sf::Event::EventType::KeyPressed: 
				switch (_event.key.code){
					case sf::Keyboard::Up: changeEntry(-1); break;
					case sf::Keyboard::Down: changeEntry(1); break;
					default: break;
				}
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

	void Menu::setFont(CMaker::Font _font)
	{
		font = _font;
	}

	Menu::PageInfo Menu::getCurrentPageInfo()
	{
		if (stackPages.empty())
			throw std::exception("You are trying to get current page when no page is on stack.");

		return stackPages.top();
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