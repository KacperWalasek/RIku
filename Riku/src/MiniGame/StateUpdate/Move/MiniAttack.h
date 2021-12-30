#pragma once
#include "IMiniMove.h"
#include "../../Unit/MiniUnit.h"
class MiniAttack :
    public IMiniMove
{
    std::pair<int, int> attackedTile;
    std::shared_ptr<MiniUnit> unit;
public:
    MiniAttack(std::pair<int, int> attackedTile, std::shared_ptr<MiniUnit> unit);

    virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const override;

    virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const override;

    virtual std::shared_ptr<IMiniMove> asPointner() const override;

};


