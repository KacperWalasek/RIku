#pragma once
#include <vector>
#include <memory>

namespace minigame
{
	class MiniUnit;
	class MiniGamePlayer
	{
	public:
		MiniGamePlayer(int index) : logicIndex(index) {};
		int logicIndex;
		std::vector<std::shared_ptr<MiniUnit>> units;
	};

}