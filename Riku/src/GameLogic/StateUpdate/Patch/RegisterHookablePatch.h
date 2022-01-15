#pragma once
#include <memory>
#include <cereal/types/string.hpp>
#include "../../Hooks/IHookable.h"

class RegisterHookablePatch
{
public:
	std::string id;
	bool add;

	RegisterHookablePatch() : id(""), add(true) {}
	RegisterHookablePatch(std::string id, bool add = true)
		: id(id), add(add)
	{}

	template <class Archive>
	void serialize(Archive& archive) 
	{
		archive(id, add);
	}

	RegisterHookablePatch& operator+=(const RegisterHookablePatch& patch)
	{
		if (id != patch.id)
			return *this;
		add = patch.add;
		return *this;
	}
};

