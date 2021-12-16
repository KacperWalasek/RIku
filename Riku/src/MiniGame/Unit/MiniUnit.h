#pragma once
#include <string>
#include "../Hooks/MiniLoadedHookable.h"
#include "../../GameLogic/IAsset.h"

class MiniUnit :
    public IMiniHookable, public IAsset
{
    std::string name;
    MiniLoadedHookable loadedHookable;
    int player;
public:
    MiniUnit(std::string name, int player, int baseMovementPoints, const std::map<std::string, sol::function>& hooks);

    int mapX = 0, mapY = 0;
    int movementPoints;
    int baseMovementPoints;
   
    virtual std::shared_ptr<IMiniMove> onDestroy(bool byOwner) override;
    virtual std::shared_ptr<IMiniMove> onTurnEnd() override;
    virtual std::shared_ptr<IMiniMove> onTurnBegin() override;
    virtual std::shared_ptr<IMiniMove> onBeingPlaced(int mapX, int mapY) override;

    virtual std::string getName() const override;

    int getMapX() const;
    int getMapY() const;
    int getPlayer() const;
};

