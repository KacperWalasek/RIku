#pragma once
#include "IMoveDescriptionHandler.h"
#include "../../GameState.h"
#include "../../LogicAssets.h"

class ChoseGuiOptionMoveHandler :
    public IMoveDescriptionHandler
{
    const LogicAssets& assets;
    const GameState& state;
public:
    ChoseGuiOptionMoveHandler(const GameState& state, const LogicAssets& assets);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

