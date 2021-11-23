#include "BuildMoveHandler.h"
#include "../Move/BuildTileObject.h"
#include "../MoveDescriptions/BuildMoveDescription.h"

std::shared_ptr<IMove> BuildMoveHandler::handleDescription(const IMoveDescription& description)
{
    const BuildMoveDescription& desc = (const BuildMoveDescription & )description;
    //TODO: numer gracza
    return std::make_shared<BuildTileObject>(0, std::pair<int, int>(desc.getMapX(), desc.getMapY()), desc.getBuilding());
}

bool BuildMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "build";
}
