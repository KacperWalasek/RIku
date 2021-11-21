#pragma once
#include "IMove.h"
#include "../../Unit/Unit.h"
#include "../Patch/Patch.h"
#include "../../LogicAssets.h"
#include <string>

class CreateUnit :
    public IMove
{
    int player;
    std::string name;
    int mapX;
    int mapY;
public:
    CreateUnit(int player, std::string unit, int mapX, int mapY);

    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;

};

