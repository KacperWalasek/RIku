#pragma once
#include "IMoveDescriptionHandler.h"
class SetNameMoveHandler :
    public IMoveDescriptionHandler
{
    GameState& state;
public:
    SetNameMoveHandler(GameState& state);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

