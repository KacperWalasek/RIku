#pragma once
#include "IMiniMoveDescriptionHandler.h"
class ResignMiniMoveHandler :
    public IMiniMoveDescriptionHandler
{
public:
    virtual std::shared_ptr<IMiniMove> handleDescription(const IMoveDescription& description) override;

    virtual bool canHandle(const IMoveDescription& description) const override;

};

