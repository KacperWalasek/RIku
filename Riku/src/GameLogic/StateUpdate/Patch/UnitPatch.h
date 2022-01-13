#pragma once
#include <memory>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>

class Unit;
class UnitPatch
{
public:
	UnitPatch() : unit(""), movementPointsChange(0) {}
	UnitPatch(std::string unit, int movementPointsChange)
		: unit(unit), movementPointsChange(movementPointsChange)
	{}
	UnitPatch(std::string unit, int mapX, int mapY)
		: unit(unit), mapX(mapX), mapY(mapY)
	{}
	UnitPatch(std::string unit, std::string name, int type)
		: unit(unit) 
	{
		switch (type)	
		{
			case 0:
				addedMiniUnits.push_back(name);
				break;
			case 1:
				addedSkills.push_back(name);
				break;
			default:
				break;
		}
	}
	std::string unit;
	std::vector<std::string> addedMiniUnits;
	std::vector<std::string> addedSkills;
	int movementPointsChange = 0;
	int mapX = -1;
	int mapY = -1;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(unit, addedMiniUnits, addedSkills, movementPointsChange, mapX, mapY);
	}

	UnitPatch& operator+=(const UnitPatch& patch)
	{
		if (unit != patch.unit)
			return *this;
		auto aUnits = patch.addedMiniUnits;
		if (aUnits.size() > 0)
			addedMiniUnits.insert(addedMiniUnits.end(), aUnits.begin(), aUnits.end());
		auto aSkills = patch.addedSkills;
		if (aSkills.size() > 0)
			addedSkills.insert(addedSkills.end(), aSkills.begin(), aSkills.end());
		movementPointsChange = movementPointsChange + patch.movementPointsChange;
		mapX = patch.mapX == -1 ? mapX : patch.mapX;
		mapY = patch.mapY == -1 ? mapY : patch.mapY;
		return *this;
	}
};

