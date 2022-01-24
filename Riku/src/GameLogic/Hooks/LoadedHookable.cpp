#include "LoadedHookable.h"
#include "../StateUpdate/Move/TestMove.h"
#include "MoveWrapper.h"


std::shared_ptr<IMove> LoadedHookable::callFuncWithNoArgs(IHookable& hookable, int mapX, int mapY, std::string name)
{
    auto func = functions.find(name);
    if (func == functions.end())
        return std::shared_ptr<IMove>();
    MoveWrapper wrapper = func->second(mapX, mapY);
    return wrapper.move;
}
std::shared_ptr<IMove> LoadedHookable::onDestroy(IHookable& hookable, int mapX, int mapY)
{
    auto func = functions.find("onDestroy");
    if (func == functions.end())
        return std::shared_ptr<IMove>();
    MoveWrapper wrapper = func->second(hookable, mapX, mapY);
    return wrapper.move;
}

std::shared_ptr<IMove> LoadedHookable::onTurnEnd(IHookable& hookable, int mapX, int mapY)
{
    return callFuncWithNoArgs(hookable, mapX, mapY, "onTurnEnd");
}

std::shared_ptr<IMove> LoadedHookable::onTurnBegin(IHookable& hookable, int mapX, int mapY)
{
    return callFuncWithNoArgs(hookable, mapX, mapY, "onTurnBegin");
}

std::shared_ptr<IMove> LoadedHookable::onBeingCreated(IHookable& hookable, int mapX, int mapY)
{
    return callFuncWithNoArgs(hookable, mapX, mapY, "onBeingCreated");
}

std::shared_ptr<IMove> LoadedHookable::onBeingPlaced(IHookable& hookable, int mapX, int mapY)
{
    auto func = functions.find("onBeingPlaced");
    if (func == functions.end())
        return std::shared_ptr<IMove>();
    MoveWrapper wrapper = func->second(hookable, mapX, mapY);
    return wrapper.move;
}

bool LoadedHookable::canBeBuilt(IHookable& hookable, const GameState& state, int mapX, int mapY)
{
    auto func = functions.find("canBeBuilt");
    if (func == functions.end())
        return true;
    return func->second(state, mapX, mapY);
}
