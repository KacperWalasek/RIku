#pragma once
#include "IMoveDescriptionHandler.h"
#include "../../GameState.h"

class BuildMoveHandler :
    public IMoveDescriptionHandler
{
    const GameState& state;
public:
    BuildMoveHandler(const GameState& state);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

