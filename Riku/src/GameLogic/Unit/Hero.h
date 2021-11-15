#pragma once
#include "Unit.h"
class Hero :
    public Unit, public IHookable
{
    // Na ten moment hardcoduje. By� mo�e kiedy� si� to zmieni
    const int requiredExp = 200;
    int lvl;
public:
    Hero(int baseMovementPoints);
    // publiczne, �eby mog�o by� zmieniane przez hooki
    int exp;

    virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;
    virtual std::shared_ptr<IMove> onTurnEnd() override;
    virtual std::shared_ptr<IMove> onTurnBegin() override;
    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
};

