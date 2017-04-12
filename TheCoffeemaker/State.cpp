#include "State.h"
#include "Game.h"

namespace CMaker {
	
	bool State::isTimeTrans()
	{
		return timeTrans;
	}

	bool State::isRendTrans()
	{
		return rendTrans;
	}

	State::State(Game* _game) : game{ _game }
	{
		timeTrans = false;
		rendTrans = false;
	}

	State::State(Game* _game, bool _timeTrans, bool _rendTrans) :
		game{ _game },
		timeTrans{ _timeTrans },
		rendTrans{ _rendTrans }
	{
		timeTrans = false;
		rendTrans = false;
	}

	State::~State()
	{
	}

}