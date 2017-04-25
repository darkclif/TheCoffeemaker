#include "PageEntry.h"

namespace CMaker {

	bool PageEntry::Trigger(EntryAction _action) {
		bool triggered = false;

		auto trigIt = trigFunctions.find(_action);
		if (trigIt != trigFunctions.end()) {
			auto& funcVect = (*trigIt).second;

			for (auto& func : funcVect) {
				func();
				triggered = true;
			}
		}

		return triggered;
	}

	void PageEntry::bindFuncton(EntryAction _action, std::function<void()> _func)
	{
		if (trigFunctions.find(_action) == trigFunctions.end()) {
			trigFunctions[_action] = std::vector<std::function<void()>>();
			trigFunctions[_action].push_back(_func);
		}
		else {
			trigFunctions[_action].push_back(_func);
		}
	}

	void PageEntry::setName(std::string _name)
	{
		name = _name;
		text.setString(_name);
	}

	sf::Text & PageEntry::getTextBox()
	{
		return text;
	}

	/* Constructor / Destructor */
	PageEntry::PageEntry(std::string _name)
	{
		setName(_name);
	}

	PageEntry::~PageEntry()
	{
	}

}