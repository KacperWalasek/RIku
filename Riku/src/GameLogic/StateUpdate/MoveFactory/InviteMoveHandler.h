#pragma once
#include "IMoveDescriptionHandler.h"

class InviteMoveHandler :
    public IMoveDescriptionHandler
{
    const GameState& state;
public:
    InviteMoveHandler(const GameState& state);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;

    virtual bool canHandle(const IMoveDescription& description) const override;

};

