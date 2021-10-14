//Kacper Walasek
#pragma once
#include "Request.h"
#include "Response.h"
#include <vector>
#include <memory>
#include "IRequestHandler.h"

class Communicator : public IRequestHandler
{
	std::vector<std::shared_ptr<IRequestHandler>> handlers;
public: 
	Communicator();
	virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) override;
	virtual bool canHandle(const Request& request) const override;
	void setHandlers(std::vector<std::shared_ptr<IRequestHandler>>&& handlers);
};

