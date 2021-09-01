#pragma once
#include "Request.h"
#include "Response.h"
#include <vector>
#include <memory>
#include "IRequestHandler.h"

class Communicator : public IRequestHandler
{
	std::vector<IRequestHandler*> handlers;
public: 
	Communicator();
	~Communicator();
	virtual Response* handleRequest(std::shared_ptr<Request> request) override;
	virtual bool canHandle(const Request& request) const override;
	void setHandlers(std::vector<IRequestHandler*>&& handlers);
};

