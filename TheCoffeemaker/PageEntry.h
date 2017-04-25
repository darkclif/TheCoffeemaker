#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <functional>

namespace CMaker {

	/* Page entry trigger type */
	enum class EntryAction {
		SELECTED,
		HIGHLIGHTED,
		ARROW_LEFT,
		ARROW_RIGHT,
		PREV_ENTRY,
		NEXT_ENTRY
	};

	/* Page entry class */
	class PageEntry
	{
	public:
		/*	Trigger stored event 
			@return - If event was triggered
		*/
		bool			Trigger(EntryAction _action);

		/*	Bind trigger to functions */
		void			bindFuncton(EntryAction _action, std::function<void()> _func);
		
		/* Set name */
		void			setName(std::string _name);

		/* Get textbox */
		sf::Text&		getTextBox();

		/* Constructor / Destructor */
						PageEntry(std::string _name);
						~PageEntry();

	private:
		/* Name of entry */
		std::string		name;

		/* Precomputed sfml text box */
		sf::Text		text;

		/* Binded functions */
		std::map< EntryAction, std::vector< std::function<void()> > > trigFunctions;
	};

}