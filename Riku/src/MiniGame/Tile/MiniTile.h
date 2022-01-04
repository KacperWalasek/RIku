#pragma once
#include <memory>
namespace minigame
{
	class MiniUnit;
	class MiniTile
	{
	public:
		std::shared_ptr<MiniUnit> unit;
	};
}

