#pragma once
#include "IMoveDescriptionHandler.h"
class HotseatCountMoveHandler :
    public IMoveDescriptionHandler
{
    GameState& state;
public:
    HotseatCountMoveHandler(GameState& state);

    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;

    virtual bool canHandle(const IMoveDescription& description) const override;

};

