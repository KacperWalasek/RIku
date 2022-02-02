#pragma once
#include "../Responses/Response.h"
#include <vector>

class IntListResponse : public Response
{
	std::vector<int> list;
public:
	IntListResponse(std::shared_ptr<Request> request, std::vector<int> list) : Response(request, true), list(list) {};
	std::vector<int> get() { return list; }
};
