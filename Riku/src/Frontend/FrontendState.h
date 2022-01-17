#pragma once
#include <vector>
#include "../GameLogic/Tile/Tile.h"
#include "../GameLogic/GameLogic.h"
#include "../GameLogic/Assets/AssetHandler.h"
#include "../GameLogic/Utils/Path.h"
// TODO: somehow get rid of this include
#include "../MiniGame/Tile/MiniTile.h"
#include "../MiniGame/Unit/MiniUnit.h"

class FrontendState
{
	GameLogic& logic;
public:
	FrontendState(GameLogic& logic);

	const std::vector<std::vector<Tile>>& getMap();
	const std::vector<std::vector<minigame::MiniTile>>& getMiniMap();
	std::map<std::string, int> getResources();
	std::map<std::string, std::string> getAvailableBuildings(int mapX, int mapY);
	std::vector<std::string> getUnitNames();
	std::vector<std::shared_ptr<const Unit>> getUnits();
	std::vector<std::shared_ptr<const minigame::MiniUnit>> getMiniUnits();
	const logic::AssetHandler& getLogicAssetHandler();
	const logic::AssetHandler& getMinigameAssetHandler();
	int getPlayerOnMove();
	Path getShortestPath(int fromX, int fromY, int toX, int toY);
	std::vector<std::vector<std::string>> getGuiOptions(int mapX, int mapY);
	std::vector<std::string> getGuiHeaders(int mapX, int mapY);
	bool isInMiniGame();
	std::vector<std::string> getSkills();
	std::map<std::string, std::string> getInvitations();
	std::map<std::string, Invitation> getInvitedPlayers();
	bool isInGame();

	void build(std::string name, int mapX, int mapY);
	void attack(int fromX, int fromY, int toX, int toY);
	void moveUnit(int fromX, int fromY, int toX, int toY);
	void finishTurn();
	void choseGuiOption(int mapX, int mapY, int index);
	void resign();
	void useSkill(std::string name, int mapX, int mapY);

	void save(std::string path);
	void load(std::string path);
	void invite(std::string ip);
	void acceptInvitation(std::string ip, int hotseadCount);
	void setName(std::string name);
	void setHotseatPlayerCount(int count);
	void startGame();
};

