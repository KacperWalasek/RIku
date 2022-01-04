#pragma once
#include "../../Unit/MiniUnit.h"

namespace minigame
{
	class MiniPlayerPatch
	{
	public:
		MiniPlayerPatch() {};
		MiniPlayerPatch(std::shared_ptr<MiniUnit> units, bool add = true)
		{
			if (add)
				addedUnits.push_back(units);
			else
				removedUnits.push_back(units);
		}
		std::vector<std::shared_ptr<MiniUnit>> addedUnits;
		std::vector<std::shared_ptr<MiniUnit>> removedUnits;
		MiniPlayerPatch& operator+=(const MiniPlayerPatch& patch)
		{
			auto aUits = patch.addedUnits;
			if (aUits.size() > 0)
				addedUnits.insert(addedUnits.end(), aUits.begin(), aUits.end());
			auto rUnits = patch.removedUnits;
			if (rUnits.size() > 0)
				removedUnits.insert(removedUnits.end(), rUnits.begin(), rUnits.end());
			return *this;
		}
	};

}