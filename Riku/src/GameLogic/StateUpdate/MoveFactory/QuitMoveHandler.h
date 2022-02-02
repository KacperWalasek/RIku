#pragma once
#include "IMoveDescriptionHandler.h"
#include "../Move/QuitGame.h"

class QuitMoveHandler :
    public IMoveDescriptionHandler
{
public:
    virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) override
    {
        return std::make_shared<QuitGame>();
    }

    virtual bool canHandle(const IMoveDescription& description) const override 
    {
        return description.getMoveType() == "quit";
    }

};

