#pragma once
#include "IMiniMoveDescriptionHandler.h"
#include "../MiniGameState.h"

class AttackMiniMoveHandler :
    public IMiniMoveDescriptionHandler
{
    const MiniGameState& state;
public:
    AttackMiniMoveHandler(const MiniGameState& state);
    virtual std::shared_ptr<IMiniMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};



