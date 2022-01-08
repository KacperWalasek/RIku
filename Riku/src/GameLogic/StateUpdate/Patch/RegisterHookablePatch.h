#pragma once
#include <memory>
#include "../../Hooks/IHookable.h"

class RegisterHookablePatch
{
public:
	std::string id;
	bool add;

	RegisterHookablePatch(std::string id, bool add = true)
		: id(id), add(add)
	{}

	RegisterHookablePatch& operator+=(const RegisterHookablePatch& patch)
	{
		if (id != patch.id)
			return *this;
		add = patch.add;
		return *this;
	}
};

