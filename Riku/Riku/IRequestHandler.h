#pragma once
#include "Request.h"
#include "Response.h"
class IRequestHandler
{
public:
	virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) = 0;
	virtual bool canHandle(const Request& request) const = 0;
};

