#pragma once
#include "IMiniMove.h"
#include <string>
class CreateMiniUnit :
    public IMiniMove
{
    std::string name;
    int mapX; 
    int mapY; 
    int player = -1;
public:
    CreateMiniUnit(std::string name, int mapX, int mapY, int player = -1);
    virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const override;
    virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const override;
    virtual std::shared_ptr<IMiniMove> asPointner() const override;
};

