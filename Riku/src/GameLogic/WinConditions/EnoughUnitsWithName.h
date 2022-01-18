#pragma once
#include "IWinCondition.h"
#include "../GameState.h"
#include "../Unit/Unit.h"
class EnoughUnitsWithName : public IWinCondition
{
public:
	int count;
	std::string name;

	EnoughUnitsWithName(int count, std::string name = "")
		: count(count), name(name) {}
	virtual int isSatisfied(const GameState& state, const LogicAssets& assets)
	{
		for (int i = 0; i < state.players.size(); i++)
		{
			int c = 0;
			const auto& units = state.players[i].units;
			for (const auto& unit : units)
				if (name == "" || unit->getName() == name)
					c++;
			if (c >= count)
				return i;
		}
		return -1;
	}
};