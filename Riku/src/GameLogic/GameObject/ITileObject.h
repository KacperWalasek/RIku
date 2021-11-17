// Kacper Walasek

#pragma once
#include "../IAsset.h"
#include "../Tile/TileCost/ICostModifier.h"
#include "../StateUpdate/Move/IMove.h"
#include "../IHOOKABLE.h"
#include <map>

class ITileObject : public IAsset, public ICostModifier, public IHookable
{
};

//
//public:
//	ITileObject(std::map<std::string, sol::function> hooks) : LoadedHookable(hooks) {};