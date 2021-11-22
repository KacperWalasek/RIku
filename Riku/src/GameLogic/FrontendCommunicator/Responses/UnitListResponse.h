#pragma once
#include "Response.h"
#include <vector>
#include "../../Unit/Unit.h"

class UnitListResponse :
    public Response
{
    std::vector<std::shared_ptr<const Unit>> units;
public:
    UnitListResponse(std::shared_ptr<Request> request, std::vector<std::shared_ptr<const Unit>> units) : Response(request, true), units(units) {}
    std::vector<std::shared_ptr<const Unit>> getUnits() { return units; }
};
