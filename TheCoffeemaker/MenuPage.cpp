#include "MenuPage.h"
#include <TheCoffeeMaker/Menu.h>
#include <TheCoffeeMaker/PageEntry.h>
#include <TheCoffeeMaker/Tools.h>

namespace CMaker {
	void MenuPage::Draw(sf::RenderWindow & _render, sf::RenderStates _states)
	{
		if (!isBuilded) {
			buildPage(_states.transform);
		}

		_render.draw(header, _states);

		for (auto& lEntry : entries) {
			_render.draw(lEntry.getTextBox(), _states);
		}
	}

	/* Entries */
	void MenuPage::addEntry(std::string _name)
	{
		entries.push_back(PageEntry(_name));
		isBuilded = false;

		if (entries.size() == 1) {
			currEntry = 0;
			updateHighlightedEntry();
		}
	}

	void MenuPage::addEntryTrigger(EntryAction _action, std::function<void()> _func)
	{
		entries.back().bindFuncton(_action, _func);
	}

	void MenuPage::Trigger(EntryAction _event)
	{
		switch (_event) {
			// Default behaviot for changing entries
			case EntryAction::NEXT_ENTRY: changeCurrentEntry(1); break;
			case EntryAction::PREV_ENTRY: changeCurrentEntry(-1); break;

			// Trigger current entry
			default: entries[currEntry].Trigger(_event); break;
		}
	}

	void MenuPage::changeCurrentEntry(int _change)
	{
		currEntry += _change;
		currEntry %= entries.size();

		updateHighlightedEntry();
	}

	void MenuPage::updateHighlightedEntry()
	{
		for (sf::Uint32 i = 0; i < entries.size(); ++i) {
			sf::Text& lText = entries[i].getTextBox();

			if (i==currEntry) {
				lText.setFillColor(style.FONT_COLOR_HIGHLIGHT);
			}
			else {
				lText.setFillColor(style.FONT_COLOR_NORMAL);
			}
		}
	}

	/* Header */
	void MenuPage::setHeader(std::string _header)
	{
		header.setString(_header);
		isBuilded = false;
	}

	sf::FloatRect MenuPage::getPageArea()
	{
		return pageArea;
	}

	/* Handle events */
	void MenuPage::checkMouseHighlight(sf::Vector2f _point)
	{
		// Not in menu area
		if (!pageArea.contains(_point))
			return;
		
		_point.x = 1.f; // We consider only _point.y to detect shorter entries

		// Check all entries of page
		for (sf::Uint32 i = 0; i < entries.size(); ++i) {
			auto& lEntry = entries[i];
			if (lEntry.getTextBox().getGlobalBounds().contains(_point)) {
				currEntry = i;
				lEntry.Trigger(EntryAction::HIGHLIGHTED);

				updateHighlightedEntry();
				return;
			}
		}
	}

	void MenuPage::checkMouseClick(sf::Vector2f _point)
	{
		// Check if current entry is clicked 
		auto& lEntry = entries[currEntry];
		
		_point.x = 1.f; // We consider only _point.y to detect shorter entries

		if (lEntry.getTextBox().getGlobalBounds().contains(_point)) {
			lEntry.Trigger(EntryAction::SELECTED);
			return;
		}
	}

	/* Build page textboxes */
	void MenuPage::buildPage(sf::Transform _transform)
	{
		int numTextBox = 0;

		// Header
		if (header.getString() != "") {
			header.setFont(ResourceMgr.getResource(style.FONT_FACE));
			header.setPosition(0.f, 0.f);
			header.move(sf::Vector2f(numTextBox * style.ENTRIES_SPACE.x, numTextBox * style.ENTRIES_SPACE.y));

			header.setOutlineThickness(style.TEXT_OUTLINE_THICKNESS);
			header.setOutlineColor(style.TEXT_OUTLINE_COLOR);

			// Expand menu area
			pageArea = header.getGlobalBounds();
			
			numTextBox += 2;
		}

		// Entries
		for (PageEntry& lEntry : entries) {
			sf::Text& lTextbox = lEntry.getTextBox();
			
			lTextbox.setFont(ResourceMgr.getResource(style.FONT_FACE));
			lTextbox.setPosition(0.f, 0.f);
			lTextbox.move(sf::Vector2f(numTextBox * style.ENTRIES_SPACE.x,numTextBox * style.ENTRIES_SPACE.y));
			
			lTextbox.setOutlineThickness(style.TEXT_OUTLINE_THICKNESS);
			lTextbox.setOutlineColor(style.TEXT_OUTLINE_COLOR);

			// Expand menu area
			if (numTextBox == 0) {
				pageArea = lTextbox.getGlobalBounds();
			}
			else {
				Tools::expandRect(pageArea, lTextbox.getGlobalBounds());
			}

			numTextBox++;
		}

		isBuilded = true;
	}

	/* Constructor / Destructor */
	MenuPage::MenuPage(Menu::MenuSettings _settings): MenuPage("", _settings)
	{
	}

	MenuPage::MenuPage(std::string _header, Menu::MenuSettings _settings):
		currEntry{0},
		style{_settings}
	{
		setHeader(_header);
	}

	MenuPage::~MenuPage()
	{
	}

}