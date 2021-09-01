#pragma once
#include "Request.h"
#include <memory>
class Response
{ 
	bool status; 
	std::shared_ptr<Request> request;
public:
	Response(std::shared_ptr<Request> request, bool status);
	bool getStatus() const;
};

