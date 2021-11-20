#pragma once
#include "Response.h"
#include <map>

class StringIntMapResponse :
    public Response
{
    std::map<std::string,int> map;
public:
    StringIntMapResponse(std::shared_ptr<Request> request, std::map<std::string, int> map) : Response(request, true), map(map) {}
    std::map<std::string, int> getMap() { return map; }
};
