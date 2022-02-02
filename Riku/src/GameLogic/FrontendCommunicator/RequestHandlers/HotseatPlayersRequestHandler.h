#pragma once
#include "IRequestHandler.h"
#include "../../GameState.h"
class HotseatPlayersRequestHandler :
    public IRequestHandler
{
    const GameState& state;
public:
    HotseatPlayersRequestHandler(const GameState& state);
    virtual std::shared_ptr<Response> handleRequest(const std::shared_ptr<Request> request) const override;

    virtual bool canHandle(const Request& request) const override;

};

