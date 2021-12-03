#pragma once
#include "IMove.h"
#include "../Patch/Patch.h"
#include "../../Hooks/MoveWrapper.h"

class CombinedMove :
    public IMove
{
    std::shared_ptr<IMove> move1, move2;
public:
    CombinedMove(MoveWrapper w1, MoveWrapper w2);
    CombinedMove(std::shared_ptr<IMove> move1, std::shared_ptr<IMove> move2);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;

    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

