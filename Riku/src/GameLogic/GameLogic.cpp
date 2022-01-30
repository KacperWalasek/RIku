// Kacper Walasek
#include "GameLogic.h"
#include <iostream>
#include <memory>
#include "Tile/MapGenerator.h"

#include "StateUpdate/MoveFactory/TestMoveHandler.h"
#include "StateUpdate/MoveFactory/BuildMoveHandler.h"
#include "StateUpdate/MoveFactory/TranslateUnitMoveHandler.h"
#include "StateUpdate/MoveFactory/ChoseGuiOptionMoveHandler.h"
#include "StateUpdate/MoveFactory/FinishGameMoveHandler.h"
#include "StateUpdate/MoveFactory/AttackMoveHandler.h"
#include "StateUpdate/MoveFactory/InviteMoveHandler.h"
#include "StateUpdate/MoveFactory/AcceptInvitationMoveHandler.h"

#include "StateUpdate/PatchHandler/PlayerOnMovePatchHandler.h"
#include "StateUpdate/PatchHandler/PlayerPatchHandler.h"
#include "StateUpdate/PatchHandler/TilePatchHandler.h"
#include "StateUpdate/PatchHandler/RegisterHookablePatchHandler.h"
#include "StateUpdate/PatchHandler/UnitPatchHandler.h"
#include "StateUpdate/PatchHandler/MiniGamePatchHandler.h"

#include "FrontendCommunicator/RequestHandlers/AvailableBuildingsRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerUnitsRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerResourcesRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/AssetHandlerRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerOnMoveRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/ShortestPathRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/TileObjectGuiRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/MapRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/IsInMiniGameRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/InvitedPlayersRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/InvitationsRequestHandler.h"

#include "FrontendCommunicator/Responses/MapResponse.h"
#include "IMiniGame.h"
#include "StateUpdate/Move/Attack.h"
#include "StateUpdate/Move/CreateUnit.h"
#include "FrontendCommunicator/Responses/IntResponse.h"
#include "Utils/LogicUtils.h"
#include "StateUpdate/MoveFactory/SaveMoveHandler.h"
#include "StateUpdate/MoveFactory/LoadMoveHandler.h"
#include "StateUpdate/PatchHandler/ClearPatchHandler.h"
#include "StateUpdate/PatchHandler/MapPatchHandler.h"
#include "StateUpdate/PatchHandler/PlayerCountPatchHandler.h"
#include "../Network/WebModule.h"
#include "Utils/Invitation.h"
#include "StateUpdate/MoveFactory/SetNameMoveHandler.h"
#include "StateUpdate/MoveFactory/StartGameMoveHandler.h"
#include "StateUpdate/PatchHandler/DelayedMovePatchHandler.h"
#include "FrontendCommunicator/RequestHandlers/GetUnitNamesRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/IsInGameRequestHandler.h"
#include <cereal/archives/binary.hpp>
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include "StateUpdate/MoveFactory/HotseatCountMoveHandler.h"
#include "../Network/InvitationAcceptance.h"
#include "FrontendCommunicator/RequestHandlers/PlayerCountRequestHandler.h"
#include "StateUpdate/PatchHandler/WinnerPatchHandler.h"
#include "FrontendCommunicator/RequestHandlers/WinnerRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PopupRequestHandler.h"


GameLogic::GameLogic(std::string assetPath, std::string minigameAssetPath) : stateUpdate(this->gameState, this->assets)
{
	assets.initialize(assetPath, minigameAssetPath);
	LogicUtils::initialize(0);
  
	stateUpdate.setHandlers({ 
		std::make_shared<ClearPatchHandler>(),
		std::make_shared<MapPatchHandler>(assets),
		std::make_shared<PlayerCountPatchHandler>(assets),
		std::make_shared<PlayerPatchHandler>(),
		std::make_shared<TilePatchHandler>(),
		std::make_shared<RegisterHookablePatchHandler>(),
		std::make_shared<UnitPatchHandler>(),
		std::make_shared<MiniGamePatchHandler>(),
		std::make_shared<DelayedMovePatchHandler>(),
		std::make_shared<PlayerOnMovePatchHandler>(),
		std::make_shared<WinnerPatchHandler>()
		});

	factory.setHandlers({
		std::make_shared<TestMoveHandler>(),
		std::make_shared<BuildMoveHandler>(gameState),
		std::make_shared<TranslateUnitMoveHandler>(),
		std::make_shared<FinishGameMoveHandler>(),
		std::make_shared<ChoseGuiOptionMoveHandler>(gameState),
		std::make_shared<AttackMoveHandler>(gameState),
		std::make_shared<SaveMoveHandler>(),
		std::make_shared<LoadMoveHandler>(gameState,assets),
		std::make_shared<InviteMoveHandler>(gameState),
		std::make_shared<AcceptInvitationMoveHandler>(gameState, assets),
		std::make_shared<SetNameMoveHandler>(gameState),
		std::make_shared<StartGameMoveHandler>(gameState),
		std::make_shared<HotseatCountMoveHandler>(gameState)
		});

	communicator.setHandlers({
		std::make_shared<MapRequestHandler>(gameState.map),
		std::make_shared<AvailableBuildingsRequestHandler>(gameState,assets),
		std::make_shared<PlayerUnitsRequestHandler>(gameState),
		std::make_shared<PlayerResourcesRequestHandler>(gameState, assets),
		std::make_shared<AssetHandlerRequestHandler>(assets),
		std::make_shared<PlayerOnMoveRequestHandler>(gameState),
		std::make_shared<ShortestPathRequestHandler>(gameState),
		std::make_shared<TileObjectGuiRequestHandler>(gameState),
		std::make_shared<IsInMiniGameRequestHandler>(gameState),
		std::make_shared<InvitedPlayersRequestHandler>(gameState),
		std::make_shared<InvitationsRequestHandler>(gameState),
		std::make_shared<GetUnitNamesRequestHandler>(assets),
		std::make_shared<IsInGameRequestHandler>(gameState),
		std::make_shared<PlayerCountRequestHandler>(gameState),
		std::make_shared<WinnerRequestHandler>(gameState),
		std::make_shared<PopupRequestHandler>()
		});
}

std::shared_ptr<Response> GameLogic::getInfo(std::shared_ptr<Request> request) const
{
	auto minigame = getActiveMiniGame();
	if (minigame)
	{
		auto response = minigame->getInfo(request);
		if (response->getStatus())
			return response;
	}

	return communicator.handleRequest(request);
}

void GameLogic::makeMove(std::shared_ptr<IMoveDescription> moveDescription)
{
	std::shared_ptr<IAction> action;
	auto minigame = getActiveMiniGame();
	if (minigame)
		action = stateUpdate.handleMove(minigame->makeMove(moveDescription));
	else
		action = stateUpdate.handleMove(factory.createMove(*moveDescription));

	if (action)
		action->takeAction(gameState, assets, stateUpdate, communicator, factory);
}

bool GameLogic::isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const
{
	auto minigame = getActiveMiniGame();
	if (minigame)
		return minigame->isMoveLegal(moveDescription);

	std::shared_ptr<IMove> move = factory.createMove(*moveDescription);
	if (!move)
		return false;
	return move->isDoable(gameState, assets);
}

void GameLogic::update()
{
	Network::m_message message = Network::WebModule::ReceiveMessageStruct();
	bool isHost = true;
	while (!message.empty())
	{
		switch (message.type())
		{
		case Network::MessType::Invitation:
			if (gameState.recivedInvitations.find(message.dataString()) == gameState.recivedInvitations.end())
				gameState.recivedInvitations.emplace(message.dataString(), message[2].to_string());
			break;
		case Network::MessType::InvitationAccepted:
			{
				InvitationAcceptance acceptance;
				acceptance.deserialize(message[2].to_string());
				auto invitationIt = gameState.invitedPlayers.find(message.dataString());
				if (invitationIt == gameState.invitedPlayers.end() || acceptance.hash != assets.handler.getHash())
					// send information
					break;
					
				invitationIt->second.state = InvitationState::Accepted;
				invitationIt->second.name = acceptance.name;
				invitationIt->second.hotseatCount = acceptance.hotseatCount;
				Network::WebModule::Join(message.dataString(), LogicUtils::getAvailablePlayerId(acceptance.hotseatCount));
			}
			break;
		case Network::MessType::Join:
			{
				for (int i = 0; i < gameState.hotSeatPlayers.size(); i++)
					gameState.hotSeatPlayers[i] += *message[2].data<int>();
			}
			break;
		case Network::MessType::JoinAccepted:
			{
				auto invitationIt = gameState.invitedPlayers.find(message.dataString());
				if (invitationIt == gameState.invitedPlayers.end())
					break;
				invitationIt->second.state = InvitationState::Joined;
			}
			break;
		case Network::MessType::Patch:
			{
				std::stringstream ss( message.dataString());
				DeserializationData data(assets, minigame::MiniGame::getAssets());
				cereal::UserDataAdapter<DeserializationData, cereal::BinaryInputArchive> iarchive(data, ss);

				std::shared_ptr<Patch> patch;
				iarchive(patch);
				stateUpdate.handlePatch(patch, false);
				if (!gameState.isInGame)
					gameState.isInGame = true;
			}
			break;
		default:
			break;
		}
		message = Network::WebModule::ReceiveMessageStruct();
	}
}

std::shared_ptr<IMiniGame> GameLogic::getActiveMiniGame() const
{
	if (gameState.minigames.size() == 1)
		return gameState.minigames.begin()->second;

	auto minigameIt = gameState.minigames.find(gameState.playerOnMove);
	if (minigameIt != gameState.minigames.end())
	{
		int playerOnMiniMove = std::static_pointer_cast<IntResponse>(
			minigameIt->second->getInfo(std::make_shared<Request>("player_on_move"))
			)->get();
		return gameState.minigames.find(playerOnMiniMove)->second;
	}
	return nullptr;
}
