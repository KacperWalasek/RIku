#include "MiniGame.h"
#include "StateUpdate/PatchHandler/IsOnMoveMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/PlayerMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/RegisterHookableMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/TileMiniPatchHandler.h"
#include "StateUpdate/PatchHandler/UnitMiniPatchHandler.h"

MiniGameAssets& MiniGame::getAssets()
{
	return assets;
}

MiniGame::MiniGame(GameState& gameState, int player, int enemy, bool begins)
	: state(gameState, player, enemy, begins), stateUpdate(state, assets)
{
	stateUpdate.setHandlers({
		std::make_shared<IsOnMoveMiniPatchHandler>(),
		std::make_shared<PlayerMiniPatchHandler>(),
		std::make_shared<RegisterHookableMiniPatchHandler>(),
		std::make_shared<TileMiniPatchHandler>(),
		std::make_shared<UnitMiniPatchHandler>()
		});
	
	std::cout << "MiniGame created"<<std::endl;
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


