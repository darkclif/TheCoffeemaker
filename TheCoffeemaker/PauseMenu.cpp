#include "PauseMenu.h"
#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>

namespace CMaker {

	/* Constructor / Destructor */
	PauseMenu::PauseMenu(Game* _game):
		Menu(_game)
	{
		// Main page
		addPage(1, "Pause menu");

		addEntry(1, "Return");
		addEventFunction(1, EntryAction::SELECTED, [this]() { getGame()->getStateMachine().reqPopState(); });
		addEntry(1, "End game");
		addEventFunctionPush(1, EntryAction::SELECTED, 2);

		// Are you sure ?
		addPage(2, "Are you sure ?");

		addEntry(2, "Yes");
		addEventFunction(2, EntryAction::SELECTED, [this]() { getGame()->getStateMachine().reqPopState(); getGame()->getStateMachine().reqPopState(); });
		addEntry(2, "No");
		addEventFunctionPush(2, EntryAction::SELECTED, 1);
	}

	PauseMenu::~PauseMenu()
	{

	}

}