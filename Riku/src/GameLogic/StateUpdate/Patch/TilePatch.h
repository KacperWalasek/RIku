#pragma once
#include <map>
#include <memory>
#include <cereal/types/utility.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include "../../GameObject/ITileObject.h"

class Unit;
class TilePatch
{
public:
	TilePatch() : tile(), unit(""), removeObject(false), removeUnit(false) {}
	TilePatch(std::pair<int, int> tile, std::shared_ptr<ITileObject> object = nullptr) 
		: tile(tile), object(object), unit(""), removeObject(false), removeUnit(false) {};
	TilePatch(std::pair<int, int> tile, std::string unit) 
		: tile(tile), object(nullptr), unit(unit), removeObject(false), removeUnit(false) {};
	TilePatch(std::pair<int, int> tile, bool removeObject, bool removeUnit) 
		: tile(tile), object(nullptr), unit(""), removeObject(removeObject), removeUnit(removeUnit) {};
	std::pair<int, int> tile;
	std::shared_ptr<ITileObject> object;
	std::string unit;
	bool removeObject;
	bool removeUnit;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(tile, object, unit, removeObject, removeUnit);
	}

	TilePatch& operator+=(const TilePatch& patch)
	{
		if (tile != patch.tile)
			return *this;
		object = (patch.object || patch.removeObject)? patch.object : object;
		unit = (patch.unit!="" || patch.removeUnit) ? patch.unit : unit;
		removeObject = patch.removeObject || (removeObject && !patch.object);
		removeUnit = patch.removeUnit || (removeUnit && patch.unit == "");
		return *this;
	}
};

