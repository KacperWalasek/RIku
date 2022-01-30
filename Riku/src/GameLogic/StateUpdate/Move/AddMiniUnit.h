#pragma once
#include "IMove.h"
#include <string>
class AddMiniUnit :
    public IMove
{
    std::string name;
    int mapX, mapY;
public:
    AddMiniUnit(std::string name, int mapX, int mapY);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

