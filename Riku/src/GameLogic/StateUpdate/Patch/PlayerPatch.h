//Kacper Walasek
#pragma once
#include <map>
#include <memory>

class Unit;
class PlayerPatch
{
public: 
	PlayerPatch(int player) :player(player) {}
	PlayerPatch(int player, int resource, int quantity) :player(player) { resourceChanges.insert({ resource,quantity }); }
	PlayerPatch(int player, std::shared_ptr<Unit> unit, bool add = true) : player(player) 
	{ 
		if (add)
			addedUnits.push_back(unit);
		else
			removedUnits.push_back(unit);
	}

	int player;
	std::map<int, int> resourceChanges;
	std::vector<std::shared_ptr<Unit>> addedUnits;
	std::vector<std::shared_ptr<Unit>> removedUnits;

	PlayerPatch& operator+=(const PlayerPatch& patch) 
	{
		if (player != patch.player)
			return *this;
		for (std::shared_ptr<Unit> unit : patch.removedUnits)
			std::remove(addedUnits.begin(), addedUnits.end(), unit);
		auto aUnits = patch.addedUnits;
		if(aUnits.size()>0)
			addedUnits.insert(addedUnits.end(), aUnits.begin(), aUnits.end());
		auto rUnits = patch.addedUnits;
		if (rUnits.size() > 0)
			removedUnits.insert(removedUnits.end(), rUnits.begin(), rUnits.end());
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
};
