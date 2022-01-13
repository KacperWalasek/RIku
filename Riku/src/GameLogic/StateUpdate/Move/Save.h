#pragma once
#include "IMove.h"
#include <string>

class Save :
    public IMove
{
    std::string fileName;
public:
    Save(std::string fileName);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

