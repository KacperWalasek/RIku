#pragma once
#include "IHookable.h"
#include "Assets/Asset.h"
class LoadedHookable
{
    const std::map<std::string, sol::function>& functions;
    std::shared_ptr<IMove> callFuncWithNoArgs(IHookable& hookable, std::string name);
public:
    LoadedHookable(const std::map<std::string, sol::function>& functions) : functions(functions) {}
    
    std::shared_ptr<IMove> onDestroy(IHookable& hookable, bool byOwner);
    std::shared_ptr<IMove> onTurnEnd(IHookable& hookable);
    std::shared_ptr<IMove> onTurnBegin(IHookable& hookable);
    std::shared_ptr<IMove> onBeingPlaced(IHookable& hookable, int mapX, int mapY);
};
