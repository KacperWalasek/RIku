#pragma once
#include <memory>
#include "../../IHookable.h"

class RegisterHookablePatch
{
public:
	std::shared_ptr<IHookable> hookable;
	bool add;

	RegisterHookablePatch(std::shared_ptr<IHookable> hookable, bool add = true)
		: hookable(hookable), add(add)
	{}

	RegisterHookablePatch& operator+=(const RegisterHookablePatch& patch)
	{
		if (hookable != patch.hookable)
			return *this;
		add = patch.add;
		return *this;
	}
};

