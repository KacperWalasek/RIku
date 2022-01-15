#include "LoadMoveHandler.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../Move/Load.h"

std::shared_ptr<IMove> LoadMoveHandler::handleDescription(const IMoveDescription& description)
{
    const StringMoveDescription& desc = (const StringMoveDescription&)description;

    return std::make_shared<Load>(desc.get());
}

bool LoadMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "load";
}