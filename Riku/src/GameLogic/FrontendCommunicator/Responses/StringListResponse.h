#pragma once
#include "Response.h"
#include <vector>

class StringListResponse :
    public Response
{
    std::vector<std::string> names;
public:
    StringListResponse(std::shared_ptr<Request> request, std::vector<std::string> names) : Response(request,true), names(names) {}
    std::vector<std::string> getNames() { return names; }
};