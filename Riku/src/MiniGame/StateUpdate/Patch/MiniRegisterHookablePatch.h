#pragma once
#include <memory>
#include "../../Hooks/IMiniHookable.h"

namespace minigame
{
	class MiniRegisterHookablePatch
	{

	public:
		std::string hookable;
		bool add;

		MiniRegisterHookablePatch(std::string hookable, bool add = true)
			: hookable(hookable), add(add)
		{}

		MiniRegisterHookablePatch& operator+=(const MiniRegisterHookablePatch& patch)
		{
			if (hookable != patch.hookable)
				return *this;
			add = patch.add;
			return *this;
		}
	};
}
