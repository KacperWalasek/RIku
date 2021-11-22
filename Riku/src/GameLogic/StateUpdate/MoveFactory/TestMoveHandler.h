#pragma once
#include "./IMoveDescriptionHandler.h"
#include "../Move/ExtractResources.h"
class TestMoveHandler : public IMoveDescriptionHandler
{
	virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
	virtual bool canHandle(const IMoveDescription& description) const override;
};

