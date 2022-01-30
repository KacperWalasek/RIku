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
		MiniRegisterHookablePatch() : hookable(""), add(false) {}
		MiniRegisterHookablePatch(std::string hookable, bool add = true)
			: hookable(hookable), add(add)
		{}

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(hookable, add);
		}

		MiniRegisterHookablePatch& operator+=(const MiniRegisterHookablePatch& patch)
		{
			if (hookable != patch.hookable)
				return *this;
			add = patch.add;
			return *this;
		}
	};
}
