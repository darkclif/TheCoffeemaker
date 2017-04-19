#pragma once
//#include <TheCoffeeMaker/Updatable.h>
#include <TheCoffeeMaker/Drawable.h>
#include <TheCoffeeMaker/Eventable.h>
#include <TheCoffeeMaker/Game.h>

#include <TheCoffeeMaker/ResourceManager.h>

#include <map>
#include <functional>
#include <stack>
#include <vector>
#include <string>
#include <memory>

namespace CMaker {

	class Menu:
		public Drawable,
		public Eventable
	{
	public:
		/* What page and what entry is activated */
		struct PageInfo {
			PageInfo(int _page, unsigned int _entry) :
				page{ _page }, entry{ _entry }
			{
			};

			int page;
			unsigned int entry;
		};

		/* Single menu entry on page with event functions */
		struct Entry {
			enum class Action {
				SELECTED,
				HIGHLIGHTED,
				ARROW_LEFT,
				ARROW_RIGHT
			};

			Entry(std::string _name) : name{ _name } {};

			/* Trigger event if exist */
			bool Trigger(Action _action) {
				bool triggered = false;

				for (auto& funcIt : actFunctions) {
					if (funcIt.first == _action) {
						funcIt.second();
						triggered = true;
					}
				}

				return triggered;
			}

			std::string name;
			sf::Text	text;
			std::map< Action, std::function<void()> > actFunctions;
		};

		/* Manage menu */
		bool						HandleInput(const sf::Event& _event);
		void						Draw(sf::RenderWindow& _render);

		/* Constructor / Destructor */
									Menu(Game* _game);
									~Menu();
	
	protected:
		/* Add empty page menu */
		void						addPage(int _page);

		/* Add entry to the end of given menu page */
		void						addEntry(int _page, std::string _name);

		/* Set starting page and entry on this page */
		void						setStartingPage(int _page, unsigned int _entry);

		/* Add event function to the last entry of given menu page */
		void						addEventFunction(int _page, Entry::Action _action, std::function<void()> _func);

		void						addEventFunctionPop(int _page, Entry::Action _action); // Pop current page if not last
		void						addEventFunctionPush(int _page, Entry::Action _action, int _targetPage); // Push next page

		/* Set font used to draw menu text */
		void						setFont(CMaker::Font _font);

		/* Get binded game instance */
		Game*						getGame();

	private:
		/* Stack with menu pages, top-most is current page info */
		std::stack< PageInfo >		stackPages;
		
		/* Map with different menu pages */
		std::map< int, std::vector<Entry> > 
									mapMenuPages;

		/* Font used to print menu */
		CMaker::Font				font;

		/* If all entries sf::Text are builded */
		bool						menuBuilded;

		/* Global bounds of menu */
		sf::FloatRect				menuArea;

		/* Game object pointer (for get world coords from mouse click events with sf::RenderWindow)*/
		CMaker::Game*				game;

	private:
		/* Trigger current entry functions */
		void						triggerCurrentEntry(Entry::Action _action);

		/* Check if mouse selected any entry of current page */
		void						checkEntryHighlight(sf::Event _event);

		/* Check if mouse clicked current selected entry*/
		void						checkMouseClick(sf::Event _event);

		/* Get currently selected entry */
		Entry&						getCurrentEntry();

		/* Get current page info */
		PageInfo&					getCurrentPageInfo();

		/* Get last entry of given page if exist */
		Entry&						getPageLastEntry(int _page);

		/* Change entry on current page */
		void						changeEntry(int _change);

		/* Pop current page */
		void						popPage();

		/* Push page */
		void						pushPage(int _page);

		/* Build and calculate all entries sf::Text */
		void						buildMenu();
	};

}