#include "RegisterHookablePatchHandler.h"

std::shared_ptr<IAction> RegisterHookablePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	for (auto p : patch.registerHookablePatches)
	{
		if (p.second.add)
			state.registredHookables.insert(p.first);
		else
			state.registredHookables.erase(p.first);
	}
	return nullptr;
}
