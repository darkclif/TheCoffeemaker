#include "PauseMenu.h"
#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>

namespace CMaker {

	/* Constructor / Destructor */
	PauseMenu::PauseMenu(Game* _game):
		Menu(_game)
	{
		// Main page
		addPage(1);

		addEntry(1, "Return");
		addEventFunction(1, EntryAction::SELECTED, [this]() { getGame()->getStateMachine().reqPopState(); });
		addEntry(1, "End game");
		addEventFunctionPush(1, EntryAction::SELECTED, 2);

		addPage(2);

		addEntry(2, "Yes");
		addEventFunction(2, EntryAction::SELECTED, [this]() { getGame()->getStateMachine().reqPopState(); getGame()->getStateMachine().reqPopState(); });
		addEntry(2, "No");
		addEventFunctionPush(2, EntryAction::SELECTED, 1);
	}

	PauseMenu::~PauseMenu()
	{

	}

}