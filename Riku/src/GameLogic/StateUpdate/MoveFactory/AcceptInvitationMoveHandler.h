#pragma once
#include "IMoveDescriptionHandler.h"
#include "../../LogicAssets.h"
class AcceptInvitationMoveHandler :
    public IMoveDescriptionHandler
{
    const LogicAssets& assets;
    GameState& state;
public:
    AcceptInvitationMoveHandler(GameState& state, const LogicAssets& assets);
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

