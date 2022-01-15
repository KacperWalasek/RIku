#pragma once
#include "Response.h"
#include <map>

class StringStringMapResponse :
    public Response
{
    std::map<std::string, std::string> map;
public:
    StringStringMapResponse(std::shared_ptr<Request> request, std::map<std::string, std::string> map) : Response(request, true), map(map) {}
    std::map<std::string, std::string> get() { return map; }
};
