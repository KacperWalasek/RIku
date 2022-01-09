#include "RegisterHookablePatchHandler.h"
#include "../../Utils/LogicUtils.h"

std::shared_ptr<IAction> RegisterHookablePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	for (auto p : patch.registerHookablePatches)
	{
		if (p.second.add)
		{
			if (state.registredHookables.find(p.first) == state.registredHookables.end())
				state.registredHookables.emplace(p.first, LogicUtils::getHookable(p.first));
		}
		else
			state.registredHookables.erase(p.first);
	}
	return nullptr;
}
