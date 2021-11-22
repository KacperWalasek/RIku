//Kacper Walasek
#pragma once
#include "Requests/Request.h"
#include "Responses/Response.h"
#include <vector>
#include <memory>
#include "RequestHandlers/IRequestHandler.h"

class Communicator : public IRequestHandler
{
	std::vector<std::shared_ptr<IRequestHandler>> handlers;
public: 
	Communicator();
	virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
	virtual bool canHandle(const Request& request) const override;
	void setHandlers(std::vector<std::shared_ptr<IRequestHandler>>&& handlers);
};

