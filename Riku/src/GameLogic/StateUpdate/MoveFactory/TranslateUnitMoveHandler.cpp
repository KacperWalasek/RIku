#include "TranslateUnitMoveHandler.h"
#include "../MoveDescriptions/TranslateUnitMoveDescription.h"
#include "../Move/TranslateUnit.h"

std::shared_ptr<IMove> TranslateUnitMoveHandler::handleDescription(const IMoveDescription& description)
{
    const auto& desc = (const TranslateUnitMoveDescription&)description;
    return std::make_shared<TranslateUnit>(desc.getFromX(),desc.getFromY(),desc.getToX(),desc.getToY());
}

bool TranslateUnitMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "translate_unit";
}
