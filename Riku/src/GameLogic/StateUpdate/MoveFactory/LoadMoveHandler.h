#pragma once
#include "IMoveDescriptionHandler.h"
#include "../../LogicAssets.h"
class LoadMoveHandler :
    public IMoveDescriptionHandler
{
    const LogicAssets& assets;
    GameState& state;
public:
    LoadMoveHandler(GameState& state, const LogicAssets& assets);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

