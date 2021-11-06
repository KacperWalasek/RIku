#include "TestMoveHandler.h"

std::shared_ptr<IMove> TestMoveHandler::handleDescription(const IMoveDescription& description)
{
	return std::make_shared<ExtractResources>(0,0,10,0,0);
}

bool TestMoveHandler::canHandle(const IMoveDescription& description) const
{
	return description.getMoveType() == "test";
}
