#pragma once
#include <memory>
#include "../Requests/Request.h"
#include "Response.h"

class BoolResponse : public Response
{
    bool response;
public:
    BoolResponse(std::shared_ptr<Request> request, bool response) : Response(request, true), response(response) {};
    bool get() { return response; }
};

