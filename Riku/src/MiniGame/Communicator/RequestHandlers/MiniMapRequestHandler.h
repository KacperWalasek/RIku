#pragma once
#include "../../../GameLogic/FrontendCommunicator/RequestHandlers/IRequestHandler.h"
#include "../../MiniGameState.h"

class MiniMapRequestHandler
	: public IRequestHandler
{
	const MiniGameState& state;
public:
	MiniMapRequestHandler(const MiniGameState& state);
	virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
	virtual bool canHandle(const Request& request) const override;
};

