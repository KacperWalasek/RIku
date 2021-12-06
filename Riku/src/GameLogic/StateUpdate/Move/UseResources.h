#pragma once
#include "IMove.h"
#include "../../GameState.h"
#include "../Patch/Patch.h"

class UseResources :
    public IMove
{
    bool asString;
    int resource, quantity;
    std::string resourceAsString;
    int getResourceFromString(const LogicAssets& assets) const;
public:
    UseResources(std::string resource, int quantity);
    UseResources(int resource, int quantity);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;

    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

