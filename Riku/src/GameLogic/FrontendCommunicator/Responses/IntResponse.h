#pragma once
#include "Response.h"
class IntResponse :
    public Response
{
    int response;
public:
    IntResponse(std::shared_ptr<Request> request, int response) : Response(request, true), response(response) {};
    int get() { return response; }
};

