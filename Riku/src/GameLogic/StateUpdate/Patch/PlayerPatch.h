//Kacper Walasek
#pragma once
#include <map>
#include <memory>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include "../../Unit/Unit.h"

class PlayerPatch
{
public:
	PlayerPatch(int player = 0) :player(player) {}
	PlayerPatch(int player, int resource, int quantity) :player(player) { resourceChanges.insert({ resource,quantity }); }
	PlayerPatch(int player, std::shared_ptr<Unit> unit) : player(player) 
	{
		addedUnits.push_back(unit);
	}
	PlayerPatch(int player, std::string removedUnit) : player(player)
	{
		removedUnits.push_back(removedUnit);
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(player, addedUnits, resourceChanges, removedUnits);
	}

	int player;
	std::map<int, int> resourceChanges;
	std::vector<std::shared_ptr<Unit>> addedUnits;
	std::vector<std::string> removedUnits;

	PlayerPatch& operator+=(const PlayerPatch& patch) 
	{
		if (player != patch.player)
			return *this;
		for (const std::string& unit : patch.removedUnits)
			std::remove_if(addedUnits.begin(), addedUnits.end(), [&](const std::shared_ptr<Unit>& addedUnit) { return addedUnit->getId() == unit; });
		auto aUnits = patch.addedUnits;
		if(aUnits.size()>0)
			addedUnits.insert(addedUnits.end(), aUnits.begin(), aUnits.end());
		auto rUnits = patch.removedUnits;
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
