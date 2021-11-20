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

    virtual std::shared_ptr<Patch> createPatch(const GameState& state) const override;
    virtual bool isDoable(const GameState& state) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;

};

