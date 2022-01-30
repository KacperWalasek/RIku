#pragma once
#include "IMiniMoveDescriptionHandler.h"

namespace minigame
{
    class FinishMiniTurnMoveHandler :
        public IMiniMoveDescriptionHandler
    {
    public:
        virtual std::shared_ptr<IMiniMove> handleDescription(const IMoveDescription& description) override;

        virtual bool canHandle(const IMoveDescription& description) const override;

    };

}