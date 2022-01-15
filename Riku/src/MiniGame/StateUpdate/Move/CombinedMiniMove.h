#pragma once
#include "IMiniMove.h"
#include "../../Hooks/MiniMoveWrapper.h"

namespace minigame
{
    class CombinedMiniMove :
        public IMiniMove
    {
        std::shared_ptr<IMiniMove> move1, move2;
    public:
        CombinedMiniMove(MiniMoveWrapper w1, MiniMoveWrapper w2);
        CombinedMiniMove(std::shared_ptr<IMiniMove> move1, std::shared_ptr<IMiniMove> move2);
        virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const override;
        virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const override;
        virtual std::shared_ptr<IMiniMove> asPointner() const override;
    };
}
