#pragma once
#include "IRequestHandler.h"
#include "../../GameState.h"
#include "../../LogicAssets.h"

class PlayerResourcesRequestHandler :
    public IRequestHandler
{
    const GameState& state;
    const LogicAssets& assets;
public:
    PlayerResourcesRequestHandler(const GameState& gamestate, const LogicAssets& assets);
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

