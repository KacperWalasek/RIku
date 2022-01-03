#pragma once
#include "IMiniMove.h"
class MiniResign :
    public IMiniMove
{
public:
    virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const override;
    virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const override;
    virtual std::shared_ptr<IMiniMove> asPointner() const override;
};

