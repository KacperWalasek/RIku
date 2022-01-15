#include "SaveMoveHandler.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../Move/Save.h"

std::shared_ptr<IMove> SaveMoveHandler::handleDescription(const IMoveDescription& description)
{
    const StringMoveDescription& desc = (const StringMoveDescription&)description;
    
    return std::make_shared<Save>(desc.get());
}

bool SaveMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "save";
}
