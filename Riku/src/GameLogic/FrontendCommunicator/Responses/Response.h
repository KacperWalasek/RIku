//Kacper Walasek
#pragma once
#include "../Requests/Request.h"
#include <memory>
class Response
{ 
	bool status; 
public:
	std::shared_ptr<Request> request;
	Response(std::shared_ptr<Request> request, bool status);
	bool getStatus() const;
};

