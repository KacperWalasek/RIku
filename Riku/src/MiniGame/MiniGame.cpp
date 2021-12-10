#include "MiniGame.h"

MiniGame::MiniGame(GameState& gameState, int player, int enemy, bool begins)
	: state(gameState, player, enemy, begins), stateUpdate(state, assets)
{}

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


