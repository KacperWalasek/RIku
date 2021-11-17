#pragma once
#include "IMove.h"
#include "../../Unit/Unit.h"
#include "../Patch/Patch.h"
#include <string>
#include "../../LogicAssets.h"
class CreateUnit :
    public IMove
{
    int player;
    std::string name;
    LogicAssets& assets;
public:
    CreateUnit(int player, std::string unit, LogicAssets& assets);
    // Odziedziczono za poœrednictwem elementu IMove
    virtual std::shared_ptr<Patch> createPatch(const GameState& state) const override;

    virtual bool isDoable(const GameState& state) const override;

};

