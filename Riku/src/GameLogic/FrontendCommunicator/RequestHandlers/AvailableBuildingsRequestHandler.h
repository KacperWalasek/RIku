#pragma once
#include "IRequestHandler.h"
#include "../../LogicAssets.h"
#include "../../GameState.h"
class AvailableBuildingsRequestHandler :
    public IRequestHandler
{
    const LogicAssets& assets;
    const GameState& state;
public:
    AvailableBuildingsRequestHandler(const GameState& state, const LogicAssets& assets) : assets(assets), state(state) {};
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};
