#pragma once
#include "IMiniMove.h"

namespace minigame
{
    class TranslateMiniUnit :
        public IMiniMove
    {
        int fromX, fromY, toX, toY;
    public:
        TranslateMiniUnit(int fromX, int fromY, int toX, int toY);
        virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const override;
        virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const override;
        virtual std::shared_ptr<IMiniMove> asPointner() const override;
    };

}