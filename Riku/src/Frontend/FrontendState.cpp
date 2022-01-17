#include "FrontendState.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/TranslateUnitMoveDescription.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/BuildMoveDescription.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/SimpleMoveDescription.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/ChoseGuiOptionMoveDescription.h"

#include "../GameLogic/FrontendCommunicator/Responses/MapResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/StringIntMapResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/StringListResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/UnitListResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/IntResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/PathResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/BoolResponse.h"
#include "../GameLogic/FrontendCommunicator/Requests/TileRequest.h"
#include "../GameLogic/FrontendCommunicator/Requests/TilePairRequest.h"
#include "../MiniGame/Communicator/Responses/MiniMapResponse.h"

#include "../GameLogic/StateUpdate/MoveDescriptions/AttackMoveDescription.h"
#include "../MiniGame/Communicator/Responses/MiniUnitListResponse.h"
#include "../MiniGame/StateUpdate/MoveDescription/UseSkillMoveDescription.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/StringMoveDescription.h"
#include "../GameLogic/FrontendCommunicator/Responses/GUIResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/StringStringMapResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/AssetHandlerResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/InvitationResponse.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/IntMoveDescription.h"

FrontendState::FrontendState(GameLogic& logic)
	: logic(logic)
{}

const std::vector<std::vector<Tile>>& FrontendState::getMap()
{
	return logic.getInfo<MapResponse>("map")->getMap();
}

const std::vector<std::vector<minigame::MiniTile>>& FrontendState::getMiniMap()
{
	return logic.getInfo<minigame::MiniMapResponse>("mini_map")->get();
}

std::map<std::string, int> FrontendState::getResources()
{
	return logic.getInfo<StringIntMapResponse>("player_resources")->getMap();
}

std::map<std::string, std::string> FrontendState::getAvailableBuildings(int mapX, int mapY)
{
	return logic.getInfo<StringStringMapResponse>(std::make_shared<TileRequest>("available_buildings", mapX, mapY))->get();
}

std::vector<std::string> FrontendState::getUnitNames()
{
	return logic.getInfo<StringListResponse>("unit_names")->getNames();
}

std::vector<std::shared_ptr<const Unit>> FrontendState::getUnits()
{
	return logic.getInfo<UnitListResponse>("player_units")->getUnits();
}

std::vector<std::shared_ptr<const minigame::MiniUnit>> FrontendState::getMiniUnits()
{
	return logic.getInfo<minigame::MiniUnitListResponse>("mini_player_units")->get();
}

const logic::AssetHandler& FrontendState::getLogicAssetHandler()
{
	return logic.getInfo<AssetHandlerResponse>("asset_handler")->getLogicHandler();
}

const logic::AssetHandler& FrontendState::getMinigameAssetHandler()
{
	return logic.getInfo<AssetHandlerResponse>("asset_handler")->getMinigameHandler();
}

int FrontendState::getPlayerOnMove()
{
	return logic.getInfo<IntResponse>("player_on_move")->get();
}

Path FrontendState::getShortestPath(int fromX, int fromY, int toX, int toY)
{
	return logic.getInfo<PathResponse>(std::make_shared<TilePairRequest>("shortest_path", fromX, fromY, toX, toY))->get();
}
std::vector<std::vector<std::string>> FrontendState::getGuiOptions(int mapX, int mapY)
{
	auto response = logic.getInfo<GUIResponse>(std::make_shared<TileRequest>("tile_object_gui", mapX, mapY));
	if (response->getStatus())
		return response->getOption();
	return {};
}

std::vector<std::string> FrontendState::getGuiHeaders(int mapX, int mapY)
{
	auto response = logic.getInfo<GUIResponse>(std::make_shared<TileRequest>("tile_object_gui", mapX, mapY));
	if (response->getStatus())
		return response->getHeaders();
	return {};
}

bool FrontendState::isInMiniGame()
{
	return logic.getInfo<BoolResponse>("is_in_minigame")->get();
}

std::vector<std::string> FrontendState::getSkills()
{
	return logic.getInfo<StringListResponse>("skills")->getNames();
}

std::map<std::string, std::string> FrontendState::getInvitations()
{
	return logic.getInfo<StringStringMapResponse>("invitations")->get();
}

std::map<std::string, Invitation> FrontendState::getInvitedPlayers()
{
	return logic.getInfo<InvitationResponse>("invited_players")->get();
}

bool FrontendState::isInGame()
{
	return logic.getInfo<BoolResponse>("is_in_game")->get();
}

void FrontendState::build(std::string name, int mapX, int mapY)
{
	logic.makeMove(std::make_shared<BuildMoveDescription>(name, mapX, mapY));
}

void FrontendState::attack(int fromX, int fromY, int toX, int toY)
{
	logic.makeMove(std::make_shared<AttackMoveDescription>(fromX, fromY, toX, toY));
}

void FrontendState::moveUnit(int fromX, int fromY, int toX, int toY)
{
	logic.makeMove(std::make_shared<TranslateUnitMoveDescription>(fromX, fromY, toX, toY));
}

void FrontendState::finishTurn()
{
	logic.makeMove(std::make_shared<SimpleMoveDescription>("finish_turn"));
}

void FrontendState::choseGuiOption(int mapX, int mapY, int index)
{
	logic.makeMove(std::make_shared<ChoseGuiOptionMoveDescription>(mapX, mapY, index));
}

void FrontendState::resign()
{
	logic.makeMove(std::make_shared<SimpleMoveDescription>("resign"));
}

void FrontendState::useSkill(std::string name, int mapX, int mapY)
{
	logic.makeMove(std::make_shared<minigame::UseSkillMoveDescription>(name, mapX, mapY));
}

void FrontendState::save(std::string path)
{
	logic.makeMove(std::make_shared<StringMoveDescription>("save", path));
}

void FrontendState::load(std::string path)
{
	logic.makeMove(std::make_shared<StringMoveDescription>("load", path));
}

void FrontendState::invite(std::string ip)
{
	logic.makeMove(std::make_shared<StringMoveDescription>("invite", ip));
}

void FrontendState::acceptInvitation(std::string ip)
{
	logic.makeMove(std::make_shared<StringMoveDescription>("accept_invitation", ip));
}

void FrontendState::setName(std::string name)
{
	logic.makeMove(std::make_shared<StringMoveDescription>("set_name", name));
}

void FrontendState::setHotseatPlayerCount(int count)
{
	logic.makeMove(std::make_shared<IntMoveDescription>("hotseat_count", count));
}

void FrontendState::startGame()
{
	logic.makeMove(std::make_shared<SimpleMoveDescription>("start_game"));
}
