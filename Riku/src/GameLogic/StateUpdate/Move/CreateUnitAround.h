#pragma once
#include "IMove.h"
#include <string>
class CreateUnitAround :
    public IMove
{
    int mapX;
    int mapY;
    std::string unit;
public:
    CreateUnitAround(std::string unit, int mapX, int mapY);

    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

