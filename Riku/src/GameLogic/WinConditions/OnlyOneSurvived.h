#pragma once
#include "../GameState.h"
#include "IWinCondition.h"

class OnlyOneSurvived : public IWinCondition
{
public:
	virtual int isSatisfied(const GameState& state, const LogicAssets& assets)
	{
		int player = -1;
		for(int i = 0; i < state.players.size(); i++)
			if (state.players[i].units.size() > 0)
				if (player == -1)
					player = i;
				else
					return -1;
		return player;
	}
};