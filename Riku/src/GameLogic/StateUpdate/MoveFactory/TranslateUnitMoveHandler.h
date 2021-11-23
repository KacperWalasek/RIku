#pragma once
#include "IMoveDescriptionHandler.h"

class TranslateUnitMoveHandler :
    public IMoveDescriptionHandler
{
public:
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override;
    virtual bool canHandle(const IMoveDescription& description) const override;
};

