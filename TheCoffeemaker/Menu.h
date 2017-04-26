#pragma once
#include <TheCoffeeMaker/Drawable.h>
#include <TheCoffeeMaker/Eventable.h>
#include <TheCoffeeMaker/Game.h>

#include <TheCoffeeMaker/ResourceManager.h>

#include <TheCoffeeMaker/PageEntry.h>

#include <SFML/Graphics.hpp>

#include <map>
#include <functional>
#include <stack>
#include <vector>
#include <string>
#include <memory>

namespace CMaker {
	class MenuPage;

	class Menu:
		public Drawable,
		public Eventable,
		public sf::Transformable
	{
	public:
		/* Manage menu */
		bool						HandleInput(const sf::Event& _event);
		void						Draw(sf::RenderWindow& _render, sf::RenderStates _states = sf::RenderStates()) override;

		/* Constructor / Destructor */
									Menu(Game* _game);
									~Menu();
	
	protected:
		/* Add empty page menu */
		void						addPage(sf::Uint32 _pageNum, std::string _header = "");

		/* Add entry to page */
		void						addEntry(sf::Uint32 _pageNum, std::string _name);

		/* Add function to last page entry */
		void						addEventFunction(sf::Uint32 _pageNum, EntryAction _action, std::function<void()> _func);
		void						addEventFunctionPop(sf::Uint32 _pageNum, EntryAction _action); // Pop current page if not last
		void						addEventFunctionPush(sf::Uint32 _pageNum, EntryAction _action, int _targetPage); // Push next page

		/* Set starting page */
		void						setStartingPage(sf::Uint32 _page);

		/* Get binded game instance */
		Game*						getGame();

	private:
		/* Stack with menu pages, top-most is current page info */
		std::stack<sf::Uint32>		stackPages;
		
		/* Map with different menu pages */
		std::map< sf::Uint32, std::unique_ptr< MenuPage > > 
									mapMenuPages;

		/* Get top page */
		MenuPage&					getCurrentPage();

		/* Global bounds of menu */
		sf::FloatRect				menuArea;

		/* Initial build of pages */
		bool						pagesBuilded;

		/* Game object pointer (for get world coords from mouse click events with sf::RenderWindow)*/
		CMaker::Game*				game;

	private:
		/* Handle mouse events */
		void						checkMouseMove(sf::Event _event);
		void						checkMouseClick(sf::Event _event);

		/* Pop, push page */
		void						popPage();
		void						pushPage(int _page);

		/* Build and calculate all pages */
		void						buildPages();

	public:
		struct MenuSettings {
			const sf::Color		FONT_COLOR_HIGHLIGHT = sf::Color(255, 23, 23);
			const sf::Color		FONT_COLOR_NORMAL = sf::Color(255, 255, 255);
			const sf::Color		TEXT_OUTLINE_COLOR = sf::Color::Black;

			const float			TEXT_OUTLINE_THICKNESS = 2.f;
			const CMaker::Font	FONT_FACE = CMaker::Font::DEFAULT;

			const sf::Vector2f	ENTRIES_SPACE = sf::Vector2f(0.f, 50.f);
		} menuStyle;
	};

}