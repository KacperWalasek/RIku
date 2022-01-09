#pragma once
#include "../../Unit/MiniUnit.h"

namespace minigame
{
	class MiniPlayerPatch
	{
	public:
		MiniPlayerPatch() {};
		MiniPlayerPatch(std::shared_ptr<MiniUnit> unit)
		{
				addedUnits.push_back(unit);
		}
		MiniPlayerPatch(std::string name, bool skill = false)
		{
			// TODO: when id will have its own type divide it to 2 constructors
			if(skill)
				usedSkills.push_back(name);
			else
				removedUnits.push_back(name);
		}
		std::vector<std::shared_ptr<MiniUnit>> addedUnits;
		std::vector<std::string> removedUnits;
		std::vector<std::string> usedSkills;

		MiniPlayerPatch& operator+=(const MiniPlayerPatch& patch)
		{
			if (patch.addedUnits.size() > 0)
				addedUnits.insert(addedUnits.end(), patch.addedUnits.begin(), patch.addedUnits.end());

			if (patch.removedUnits.size() > 0)
				removedUnits.insert(removedUnits.end(), patch.removedUnits.begin(), patch.removedUnits.end());

			if (patch.usedSkills.size() > 0)
				usedSkills.insert(usedSkills.end(), patch.usedSkills.begin(), patch.usedSkills.end());

			return *this;
		}
	};

}