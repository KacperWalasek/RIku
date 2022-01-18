#pragma once
#include "IRequestHandler.h"
#include "../../GameState.h"
class PlayerCountRequestHandler :
    public IRequestHandler
{
    const GameState& state;
public:
    PlayerCountRequestHandler(const GameState& state);
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

