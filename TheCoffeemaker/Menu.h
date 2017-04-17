#pragma once
//#include <TheCoffeeMaker/Updatable.h>
#include <TheCoffeeMaker/Drawable.h>
#include <TheCoffeeMaker/Eventable.h>

#include <TheCoffeeMaker/ResourceManager.h>

#include <map>
#include <functional>
#include <stack>
#include <vector>
#include <string>
#include <memory>

namespace CMaker {

	class Menu:
		//public Updatable,
		public Drawable,
		public Eventable
	{
	public:
		bool						HandleInput(const sf::Event& _event);
		void						Draw(sf::RenderWindow& _render);

									Menu();
									~Menu();
	
	//TODO: protected:
		/* Add empty page menu */
		void						addPage(int _page);

		/* Add entry to the end of given menu page */
		void						addEntry(int _page, std::string _name);

		/* Set starting page and entry on this page */
		void						setStartingPage(int _page, unsigned int _entry);

		/* Add event function to the last entry of given menu page */
		void						addEventFunction(int _page, sf::Keyboard::Key _key, std::function<void()> _func);
		void						addEventFunctionPop(int _page, sf::Keyboard::Key _key); // Pop current page if not last
		void						addEventFunctionPush(int _page, sf::Keyboard::Key _key, int _targetPage); // Push next page

		/* Set font used to draw menu text */
		void						setFont(CMaker::Font _font);

	private:
		/* What page and what entry is activated */
		struct PageInfo {
			PageInfo(int _page, unsigned int _entry):
				page{ _page }, entry{ _entry }
			{
			};

			int page;
			unsigned int entry;
		};

		/* Single menu entry on page with functions */
		struct Entry {
			Entry(std::string _name) : name{ _name } {};

			std::string name;
			std::vector< std::pair< sf::Keyboard::Key, std::function<void()> > > 
						actions;
		};

		/* Stack with menu pages, top-most is current page info */
		std::stack< PageInfo >		stackPages;
		
		/* Map with different menu pages */
		std::map< int, std::vector<Entry> > 
									mapMenuPages;

		/* Font used to print menu */
		CMaker::Font				font;

	private:
		/* Trigger current entry functions */
		void						triggerCurrentEntry(sf::Keyboard::Key _key);

		/* Get current page info */
		PageInfo					getCurrentPageInfo();

		/* Get last entry of given page if exist */
		Entry&						getPageLastEntry(int _page);

		/* Change entry on current page */
		void						changeEntry(int _change);

		/* Pop current page */
		void						popPage();

		/* Push page */
		void						pushPage(int _page);
	};

}