#pragma once
#include "IMoveDescriptionHandler.h"

class InviteMoveHandler :
    public IMoveDescriptionHandler
{
    GameState& state;
public:
    InviteMoveHandler(GameState& state);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;

    virtual bool canHandle(const IMoveDescription& description) const override;

};

