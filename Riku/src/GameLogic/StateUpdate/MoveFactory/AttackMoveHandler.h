#pragma once
#include "IMoveDescriptionHandler.h"
class AttackMoveHandler :
    public IMoveDescriptionHandler
{
    const GameState& state;
public:
    AttackMoveHandler(const GameState& state);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

