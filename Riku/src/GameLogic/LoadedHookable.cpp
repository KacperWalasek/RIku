#include "LoadedHookable.h"
#include "StateUpdate/Move/TestMove.h"
#include "MoveWrapper.h"


std::shared_ptr<IMove> LoadedHookable::callFuncWithNoArgs(IHookable& hookable, std::string name)
{
    auto func = functions.find(name);
    if (func == functions.end())
        return std::shared_ptr<IMove>();
    MoveWrapper wrapper = func->second(hookable);
    return wrapper.move;
}
std::shared_ptr<IMove> LoadedHookable::onDestroy(IHookable& hookable, bool byOwner)
{
    auto func = functions.find("onDestroy");
    if (func == functions.end())
        return std::shared_ptr<IMove>();
    MoveWrapper wrapper = func->second(hookable, byOwner);
    return wrapper.move;
}

std::shared_ptr<IMove> LoadedHookable::onTurnEnd(IHookable& hookable)
{
    return callFuncWithNoArgs(hookable, "onTurnEnd");
}

std::shared_ptr<IMove> LoadedHookable::onTurnBegin(IHookable& hookable)
{
    return callFuncWithNoArgs(hookable, "onTurnBegin");
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
