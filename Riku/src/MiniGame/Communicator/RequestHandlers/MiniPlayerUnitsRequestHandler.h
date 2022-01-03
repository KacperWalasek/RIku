#pragma once
#include "../../../GameLogic/FrontendCommunicator/RequestHandlers/IRequestHandler.h"
#include "../../MiniGameState.h"

class MiniPlayerUnitsRequestHandler :
    public IRequestHandler
{
    const MiniGameState& state;
public:
    MiniPlayerUnitsRequestHandler(const MiniGameState& gameState);
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

