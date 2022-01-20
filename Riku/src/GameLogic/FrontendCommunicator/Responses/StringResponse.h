#pragma once
#include "Response.h"
class StringResponse :
    public Response
{
    std::string response;
public:
    StringResponse(std::shared_ptr<Request> request, std::string response) : Response(request, true), response(response) {};
    std::string get() { return response; }
};

