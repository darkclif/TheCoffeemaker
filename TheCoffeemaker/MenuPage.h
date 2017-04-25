#pragma once
#include <TheCoffeeMaker/PageEntry.h>
#include <TheCoffeeMaker/Drawable.h>
#include <TheCoffeeMaker/Menu.h>

#include <string>
#include <vector>

namespace CMaker {

	class MenuPage:
		public Drawable
	{
	public:
		/* Draw page */
		void						Draw(sf::RenderWindow& _render, sf::RenderStates _states = sf::RenderStates()) override;

		/* Entries setters */
		void						addEntry(std::string _name);

		/* Add trigger to last added entry */
		void						addEntryTrigger(EntryAction _action, std::function<void()> _func);

		/* Trigger entry function */
		void						Trigger(EntryAction _event);

		/* Handle events */
		void						checkMouseHighlight(sf::Vector2f _point);
		void						checkMouseClick(sf::Vector2f _point);

		/* Header setter */
		void						setHeader(std::string _header);

		/* Get area of page */
		sf::FloatRect				getPageArea();

		/* Calculate page textboxes */
		void						buildPage(sf::Transform _transform);

		/* Constructor / Destructor */
									MenuPage(std::string _header, Menu::MenuSettings _settings);
									MenuPage(Menu::MenuSettings _settings);
									~MenuPage();
	private:
		/* Menage currently selected entry */
		void						changeCurrentEntry(int _change);

		/* Update highlighted textbox */
		void						updateHighlightedEntry();

	private:
		/* Is page textboxes are computed */
		bool						isBuilded;

		/* Page area */
		sf::FloatRect				pageArea;

		/* Page entries */
		std::vector< PageEntry >	entries;

		/* Current selected entry */
		sf::Uint32					currEntry;

		/* Page header */
		sf::Text					header;

		/* Page settings */
		Menu::MenuSettings			style;
	};

}