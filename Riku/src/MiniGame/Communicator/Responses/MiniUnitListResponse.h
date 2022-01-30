#pragma once
#include <vector>
#include "../../../GameLogic/FrontendCommunicator/Responses/Response.h"
#include "../../Unit/MiniUnit.h"

namespace minigame
{
    class MiniUnitListResponse :
        public Response
    {
        std::vector<std::shared_ptr<const MiniUnit>> units;
    public:
        MiniUnitListResponse(std::shared_ptr<Request> request, std::vector<std::shared_ptr<const MiniUnit>> units)
            : Response(request, true), units(units) {}
        std::vector<std::shared_ptr<const MiniUnit>> get() { return units; }
    };
}
