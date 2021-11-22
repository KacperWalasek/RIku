#pragma once
#include "IMove.h"
#include "../../GameState.h"
#include "../Patch/Patch.h"

class UseResources :
    public IMove
{
    int resource, quantity;
public:
    UseResources(int resource, int quantity);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;

    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

