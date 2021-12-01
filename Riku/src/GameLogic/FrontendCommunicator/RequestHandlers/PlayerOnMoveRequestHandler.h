#pragma once
#include "IRequestHandler.h"
#include "../../GameState.h"
class PlayerOnMoveRequestHandler :
    public IRequestHandler
{
    const GameState& state;
public:
    PlayerOnMoveRequestHandler(const GameState& state);
    // Odziedziczono za poœrednictwem elementu IRequestHandler
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

