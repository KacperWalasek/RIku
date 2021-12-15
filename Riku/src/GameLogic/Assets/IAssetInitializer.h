#pragma once
#include <memory>
#include <sol\sol.hpp>
class IAssetInitializer
{
public: 
	virtual void initAsset(std::shared_ptr<sol::state> lua) const = 0;
};

