#pragma once
#include "IMoveDescriptionHandler.h"
class StartGameMoveHandler :
    public IMoveDescriptionHandler
{
    GameState& state;
public:
    StartGameMoveHandler(GameState& state);

    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

