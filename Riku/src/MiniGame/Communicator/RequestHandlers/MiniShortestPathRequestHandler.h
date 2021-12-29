#pragma once
#include "../../../GameLogic/FrontendCommunicator/RequestHandlers/IRequestHandler.h"
#include "../../MiniGameState.h"

class MiniShortestPathRequestHandler :
    public IRequestHandler
{
    const MiniGameState& state;
public:
    MiniShortestPathRequestHandler(const MiniGameState& state);
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

