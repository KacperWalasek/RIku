#pragma once
#include "../../../GameLogic/StateUpdate/MoveDescriptions/IMoveDescription.h"

namespace minigame {
    class UseSkillMoveDescription :
        public IMoveDescription
    {
        std::string name;
        int mapX, mapY;
    public:
        UseSkillMoveDescription(std::string name, int mapX, int mapY) : name(name), mapX(mapX), mapY(mapY) {}
        virtual std::string getMoveType() const override { return "use_skill"; }

        int getMapX() const { return mapX; }
        int getMapY() const { return mapY; }
        std::string getName() const { return name; }
    };
}

