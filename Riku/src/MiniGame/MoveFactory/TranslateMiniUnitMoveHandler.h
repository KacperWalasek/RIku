#pragma once
#include "IMiniMoveDescriptionHandler.h"

namespace minigame
{
	class TranslateMiniUnitMoveHandler :
		public IMiniMoveDescriptionHandler
	{
	public:
		virtual std::shared_ptr<IMiniMove> handleDescription(const IMoveDescription& description);
		virtual bool canHandle(const IMoveDescription& description) const;
	};
}
