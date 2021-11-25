#include "FrontendState.h"
#include "../GameLogic/FrontendCommunicator/Responses/MapResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/StringIntMapResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/StringListResponse.h"
#include "../GameLogic/FrontendCommunicator/Responses/UnitListResponse.h"
#include "../GameLogic/FrontendCommunicator/Requests/TileRequest.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/TranslateUnitMoveDescription.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/BuildMoveDescription.h"
#include "../GameLogic/StateUpdate/MoveDescriptions/SimpleMoveDescription.h"

FrontendState::FrontendState(GameLogic& logic)
	: logic(logic)
{}

const std::vector<std::vector<Tile>>& FrontendState::getMap()
{
	return logic.getInfo<MapResponse>("map")->getMap();
}

std::map<std::string, int> FrontendState::getResources()
{
	return logic.getInfo<StringIntMapResponse>("player_resources")->getMap();
}

std::vector<std::string> FrontendState::getAvailableBuildings(int mapX, int mapY)
{
	return logic.getInfo<StringListResponse>(std::make_shared<TileRequest>("available_buildings", mapX, mapY))->getNames();
}

std::vector<std::shared_ptr<const Unit>> FrontendState::getUnits()
{
	return logic.getInfo<UnitListResponse>("player_units")->getUnits();
}

void FrontendState::build(std::string name, int mapX, int mapY)
{
	logic.makeMove(std::make_shared<BuildMoveDescription>(name, mapX, mapY));
}

void FrontendState::moveUnit(int fromX, int fromY, int toX, int toY)
{
	logic.makeMove(std::make_shared<TranslateUnitMoveDescription>(fromX, fromY, toX, toY));
}

void FrontendState::finishTurn()
{
	logic.makeMove(std::make_shared<SimpleMoveDescription>("finish_turn"));
}
