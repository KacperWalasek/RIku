#pragma once
#include "IWinCondition.h"
#include "../GameState.h"
#include "../LogicAssets.h"
#include "../Unit/Unit.h"
class EnoughResourceOfType : public IWinCondition
{
public:
	int count;
	std::string name;

	EnoughResourceOfType(int count, std::string name)
		: count(count), name(name) {}
	virtual int isSatisfied(const GameState& state, const LogicAssets& assets)
	{
		auto it = std::find_if(assets.playerResources.begin(), assets.playerResources.end(), [&](const Resource& resource) {
			return resource.getName() == name;
		});
		int resourceIndex = std::distance(assets.playerResources.begin(), it);
		if (resourceIndex >= assets.playerResources.size())
			return -1;

		for (int i = 0; i < state.players.size(); i++)
			if (state.players[i].getResourceQuantity(resourceIndex) >= count)
				return i;
		return -1;
	}
};