#pragma once
#include <vector>
#include <memory>
#include "../../GameLogic/Unit/Unit.h"

namespace minigame
{
	class MiniUnit;
	class MiniGamePlayer
	{
	public:
		MiniGamePlayer(const Unit& logicUnit) : logicIndex(logicUnit.getOwner()), logicUnit(logicUnit), skills(logicUnit.skills) {};
		int logicIndex;
		const Unit& logicUnit;
		std::vector<std::shared_ptr<MiniUnit>> units;
		std::vector<std::string> skills;
	};

}