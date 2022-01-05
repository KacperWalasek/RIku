#include "MiniGame.h"
#include "StateUpdate/PatchHandler/IsOnMoveMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/PlayerMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/RegisterHookableMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/TileMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/UnitMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/WinnerMiniPatchHandler.h"

#include "Communicator/RequestHandlers/MiniMapRequestHandler.h"
#include "Communicator/RequestHandlers/MiniShortestPathRequestHandler.h"
#include "Communicator/RequestHandlers/PlayerOnMoveMiniRequestHandler.h"
#include "Communicator/RequestHandlers/MiniPlayerUnitsRequestHandler.h"

#include "MoveFactory/TranslateMiniUnitMoveHandler.h"
#include "MoveFactory/AttackMiniMoveHandler.h"
#include "MoveFactory/FinishMiniTurnMoveHandler.h"
#include "MoveFactory/ResignMiniMoveHandler.h"

#include "StateUpdate/Move/CreateMiniUnit.h"

minigame::MiniGameAssets& minigame::MiniGame::getAssets()
{
	return assets;
}

minigame::MiniGame::MiniGame(const Unit& player, const Unit& enemy, bool begins)
	: state(player.getOwner(), enemy.getOwner(), begins), stateUpdate(state, assets)
{
	stateUpdate.setHandlers({
		std::make_shared<IsOnMoveMiniPatchHandler>(),
		std::make_shared<PlayerMiniPatchHandler>(),
		std::make_shared<RegisterHookableMiniPatchHandler>(),
		std::make_shared<TileMiniPatchHandler>(),
		std::make_shared<UnitMiniPatchHandler>(),
		std::make_shared<WinnerMiniPatchHandler>()
		});
	
	communicator.setHandlers({
		std::make_shared<MiniMapRequestHandler>(state),
		std::make_shared<MiniShortestPathRequestHandler>(state),
		std::make_shared<PlayerOnMoveMiniRequestHandler>(state),
		std::make_shared<MiniPlayerUnitsRequestHandler>(state)
		});

	factory.setHandlers({
		std::make_shared<TranslateMiniUnitMoveHandler>(),
		std::make_shared<AttackMiniMoveHandler>(state),
		std::make_shared<FinishMiniTurnMoveHandler>(),
		std::make_shared<ResignMiniMoveHandler>()
		});

	for (int i = 0; i < 20; i++)
	{
		state.map.emplace_back();
		for (int j = 0; j < 20; j++)
			state.map[i].emplace_back();
	}
	if (begins) {
		for (int i = 0; i<player.miniunits.size(); i++)
		{
			auto createUnit = std::make_shared<CreateMiniUnit>(player.miniunits[i], i%mapsize, floor(i / mapsize), false);
			stateUpdate.handleMove(createUnit);
		}
		for (int i = 0; i < enemy.miniunits.size(); i++)
		{
			auto createUnit = std::make_shared<CreateMiniUnit>(enemy.miniunits[i], i % mapsize, mapsize - 1 - (int)floor(i / mapsize), true);
			stateUpdate.handleMove(createUnit);
		}
	}
}

std::shared_ptr<IMove> minigame::MiniGame::makeMove(std::shared_ptr<IMoveDescription> moveDescription)
{
	return stateUpdate.handleMove(factory.createMove(*moveDescription));
}

bool minigame::MiniGame::isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const
{
	std::shared_ptr<IMiniMove> move = factory.createMove(*moveDescription);
	if (!move)
		return false;
	return move->isDoable(state, assets);
}

void minigame::MiniGame::applyMiniPatch(std::shared_ptr<MiniPatch> patch)
{
	auto enemyPatch = patch->enemyPatch;
	patch->enemyPatch = patch->playerPatch;
	patch->playerPatch = enemyPatch;
	stateUpdate.handlePatch(patch);
}

std::shared_ptr<minigame::MiniPatch> minigame::MiniGame::getCummulatedPatch() const
{
	return stateUpdate.getCummulatedPatch();
}

void minigame::MiniGame::resetCummulatedPatch()
{
	stateUpdate.resetCummulatedPatch();
}

std::shared_ptr<Response> minigame::MiniGame::getInfo(std::shared_ptr<Request> request) const
{
	return communicator.handleRequest(request);
}


