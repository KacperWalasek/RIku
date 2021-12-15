#include "MiniLoadedHookable.h"
#include "MiniMoveWrapper.h"


std::shared_ptr<IMiniMove> MiniLoadedHookable::callFuncWithNoArgs(IMiniHookable& hookable, std::string name)
{
    auto func = functions.find(name);
    if (func == functions.end())
        return std::shared_ptr<IMiniMove>();
    MiniMoveWrapper wrapper = func->second(hookable);
    return wrapper.move;
}
std::shared_ptr<IMiniMove> MiniLoadedHookable::onDestroy(IMiniHookable& hookable, bool byOwner)
{
    auto func = functions.find("onDestroy");
    if (func == functions.end())
        return std::shared_ptr<IMiniMove>();
    MiniMoveWrapper wrapper = func->second(hookable, byOwner);
    return wrapper.move;
}

std::shared_ptr<IMiniMove> MiniLoadedHookable::onTurnEnd(IMiniHookable& hookable)
{
    return callFuncWithNoArgs(hookable, "onTurnEnd");
}

std::shared_ptr<IMiniMove> MiniLoadedHookable::onTurnBegin(IMiniHookable& hookable)
{
    return callFuncWithNoArgs(hookable, "onTurnBegin");
}

std::shared_ptr<IMiniMove> MiniLoadedHookable::onBeingPlaced(IMiniHookable& hookable, int mapX, int mapY)
{
    auto func = functions.find("onBeingPlaced");
    if (func == functions.end())
        return std::shared_ptr<IMiniMove>();
    MiniMoveWrapper wrapper = func->second(hookable, mapX, mapY);
    return wrapper.move;
}

