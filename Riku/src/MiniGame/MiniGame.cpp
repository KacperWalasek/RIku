#include "MiniGame.h"
#include "StateUpdate/PatchHandler/IsOnMoveMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/PlayerMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/RegisterHookableMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/TileMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/UnitMiniPatchHandler.h"
#include "StateUpdate/Move/CreateMiniUnit.h"

MiniGameAssets& MiniGame::getAssets()
{
	return assets;
}

MiniGame::MiniGame( int player, int enemy, bool begins)
	: state(player, enemy, begins), stateUpdate(state, assets)
{
	stateUpdate.setHandlers({
		std::make_shared<IsOnMoveMiniPatchHandler>(),
		std::make_shared<PlayerMiniPatchHandler>(),
		std::make_shared<RegisterHookableMiniPatchHandler>(),
		std::make_shared<TileMiniPatchHandler>(),
		std::make_shared<UnitMiniPatchHandler>()
		});
	
	std::cout << "MiniGame created"<<std::endl;

	for (int i = 0; i < 20; i++)
	{
		state.map.emplace_back();
		for (int j = 0; j < 20; j++)
			state.map[i].emplace_back();
	}

	auto createUnit = std::make_shared<CreateMiniUnit>("maciek_syn_stefana", 1, 2, false);
	auto createUnit1 = std::make_shared<CreateMiniUnit>("julka_ciocia_stefana", 2, 2, true);
	stateUpdate.handleMove(createUnit);
	stateUpdate.handleMove(createUnit1);
	std::cout << state.map[1][2].unit->getName()<<std::endl;
}

void MiniGame::makeMove(std::shared_ptr<IMoveDescription> moveDescription)
{
	stateUpdate.handleMove(factory.createMove(*moveDescription));
}

bool MiniGame::isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const
{
	std::shared_ptr<IMiniMove> move = factory.createMove(*moveDescription);
	if (!move)
		return false;
	return move->isDoable(state, assets);
}

std::shared_ptr<Response> MiniGame::getInfo(std::shared_ptr<Request> request) const
{
	return communicator.handleRequest(request);
}


