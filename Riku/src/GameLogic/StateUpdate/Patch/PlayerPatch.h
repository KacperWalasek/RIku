//Kacper Walasek
#pragma once
#include <map>
#include "../../Unit/Unit.h"

class PlayerPatch
{
public: 
	PlayerPatch(int player) :player(player) {}
	PlayerPatch(int player, int resource, int quantity) :player(player) { resourceChanges.insert({ resource,quantity }); }
	PlayerPatch(int player, std::shared_ptr<Unit> added) : player(player) { addedUnits.push_back(added);  }

	int player;
	std::map<int, int> resourceChanges;
	std::vector<std::shared_ptr<Unit>> addedUnits;

	PlayerPatch& operator+=(const PlayerPatch& patch) 
	{
		if (player != patch.player)
			return *this;
		auto units = patch.addedUnits;
		units.insert(addedUnits.end(), units.begin(), units.end());
		for (auto& resourceChange : patch.resourceChanges)
		{
			auto resource1 = resourceChanges.find(resourceChange.first);
			if (resource1 == resourceChanges.end())
				resourceChanges.insert({ resourceChange });
			else
				resource1->second += resourceChange.second;
		}
		return *this;
	}
	friend PlayerPatch operator+(PlayerPatch& p1, const PlayerPatch& p2)
	{
		if (p1.player != p2.player)
			return p1;
		auto units = p2.addedUnits;
		units.insert(p1.addedUnits.end(), units.begin(), units.end());
		for (auto& resourceChange : p2.resourceChanges)
		{
			auto resource1 = p1.resourceChanges.find(resourceChange.first);
			if (resource1 == p1.resourceChanges.end())
				p1.resourceChanges.insert({ resourceChange });
			else
				resource1->second += resourceChange.second;
		}
		return std::move(p1);
	}
};
