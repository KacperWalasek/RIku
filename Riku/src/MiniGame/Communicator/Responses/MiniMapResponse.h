#pragma once
#include <vector>
#include "../../../GameLogic/FrontendCommunicator/Responses/Response.h"
#include "../../Tile/MiniTile.h"

class MiniMapResponse :
    public Response
{
    const std::vector<std::vector<MiniTile>>& map;
public:
    MiniMapResponse(std::shared_ptr<Request> request, const std::vector<std::vector<MiniTile>>& map) 
        : Response(request, true), map(map) {}
    const std::vector<std::vector<MiniTile>>& get() 
    {
        return map;
    };
};

