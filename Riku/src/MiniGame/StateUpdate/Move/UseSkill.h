#pragma once
#include "IMiniMove.h"
#include <string>
namespace minigame {
    class UseSkill :
        public IMiniMove
    {
        std::string name;
        int mapX, mapY;
    public:
        UseSkill(std::string name, int mapX, int mapY);
        virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const override;
        virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const override;
        virtual std::shared_ptr<IMiniMove> asPointner() const override;
    };
}

