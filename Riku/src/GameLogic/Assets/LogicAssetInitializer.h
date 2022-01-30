#pragma once
#include "IAssetInitializer.h"
class LogicAssetInitializer :
    public IAssetInitializer
{
public:
    virtual void initAsset(std::shared_ptr<sol::state> lua) const override;
};

