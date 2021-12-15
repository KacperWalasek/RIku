#pragma once
#include "IMiniHookable.h"
#include <map>
#include "sol/sol.hpp"

class MiniLoadedHookable
{
    const std::map<std::string, sol::function>& functions;
    std::shared_ptr<IMiniMove> callFuncWithNoArgs(IMiniHookable& hookable, std::string name);
public:
    MiniLoadedHookable(const std::map<std::string, sol::function>& functions) : functions(functions) {}

    std::shared_ptr<IMiniMove> onDestroy(IMiniHookable& hookable, bool byOwner);
    std::shared_ptr<IMiniMove> onTurnEnd(IMiniHookable& hookable);
    std::shared_ptr<IMiniMove> onTurnBegin(IMiniHookable& hookable);
    std::shared_ptr<IMiniMove> onBeingPlaced(IMiniHookable& hookable, int mapX, int mapY);
};

