#pragma once
#include "Response.h"
#include <vector>
class PositionListResponse :
    public Response
{
    std::vector<std::pair<int, int>> list;
public:
    PositionListResponse(std::shared_ptr<Request> request, std::vector<std::pair<int, int>> list)
        : Response(request, true), list(list) {}

    std::vector<std::pair<int, int>> get() { return list; }
};

