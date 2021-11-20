#pragma once
#include "IRequestHandler.h"
#include "../../GameState.h"

class PlayerUnitsRequestHandler :
    public IRequestHandler
{
    const Player& player;
public:
    PlayerUnitsRequestHandler(const GameState& gameState);
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) override;
    virtual bool canHandle(const Request& request) const override;
};

