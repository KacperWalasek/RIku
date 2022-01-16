#pragma once
#include "IMoveDescriptionHandler.h"
class AcceptInvitationMoveHandler :
    public IMoveDescriptionHandler
{
    GameState& state;
public:
    AcceptInvitationMoveHandler(GameState& state);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

