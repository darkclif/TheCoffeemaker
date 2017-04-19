#include "MainMenu.h"
#include <TheCoffeeMaker/Game.h>
#include <TheCoffeeMaker/StateMachine.h>

namespace CMaker {

	/* Constructor / Destructor */
	MainMenu::MainMenu(Game* _game):
		Menu(_game)
	{
		// Main page
		addPage(1);

		addEntry(1, "Start");
		addEventFunction(1, Menu::Entry::Action::SELECTED, [this]() { getGame()->getStateMachine().reqPushState(EnumState::GAME_LEVEL); });
		addEntry(1, "Options");
		addEventFunctionPush(1, Menu::Entry::Action::SELECTED, 2);
		addEntry(1, "Credits");
		addEntry(1, "Exit");
		addEventFunction(1, Menu::Entry::Action::SELECTED, [this]() { getGame()->getStateMachine().reqStackClear(); });

		// Options page
		addPage(2);

		addEntry(2, "Player");
		addEntry(2, "Back");
		addEventFunctionPop(2, Menu::Entry::Action::SELECTED);
	}

	MainMenu::~MainMenu()
	{
	}

}