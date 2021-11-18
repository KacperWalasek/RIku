#pragma once
#include "Unit.h"
class Hero :
    public Unit
{
    // Na ten moment hardcoduje. Byæ mo¿e kiedyœ siê to zmieni
    const int requiredExp = 200;
    int lvl;
public:
    Hero(int baseMovementPoints, std::string name, const std::map<std::string, sol::function>& hooks);
    // publiczne, ¿eby mog³o byæ zmieniane przez hooki
    int exp;

    virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;
    virtual std::shared_ptr<IMove> onTurnEnd() override;
    virtual std::shared_ptr<IMove> onTurnBegin() override;
    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
};

