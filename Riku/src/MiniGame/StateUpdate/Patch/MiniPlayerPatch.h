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
		MiniPlayerPatch(std::shared_ptr<MiniUnit> units, std::string usedSkill)
			: usedSkills({usedSkill})
		{}
		std::vector<std::shared_ptr<MiniUnit>> addedUnits;
		std::vector<std::shared_ptr<MiniUnit>> removedUnits;
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