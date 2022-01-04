#pragma once
#include <vector>
#include "../GameLogic/Tile/Tile.h"
#include "../GameLogic/GameLogic.h"
#include "../GameLogic/Assets/AssetHandler.h"
#include "../GameLogic/Utils/Path.h"
// TODO: somehow get rid of this include
#include "../MiniGame/Tile/MiniTile.h"
class FrontendState
{
	GameLogic& logic;
public:
	FrontendState(GameLogic& logic);

	const std::vector<std::vector<Tile>>& getMap();
	const std::vector<std::vector<minigame::MiniTile>>& getMiniMap();
	std::map<std::string, int> getResources();
	std::vector<std::string> getAvailableBuildings(int mapX, int mapY);
	std::vector<std::shared_ptr<const Unit>> getUnits();
	std::vector<std::shared_ptr<const minigame::MiniUnit>> getMiniUnits();
	const logic::AssetHandler& getAssetHandler();
	int getPlayerOnMove();
	Path getShortestPath(int fromX, int fromY, int toX, int toY);
	std::vector<std::string> getGuiOptions(int mapX, int mapY);
	bool isInMiniGame();

	void build(std::string name, int mapX, int mapY);
	void attack(int fromX, int fromY, int toX, int toY);
	void moveUnit(int fromX, int fromY, int toX, int toY);
	void finishTurn();
	void choseGuiOption(int mapX, int mapY, int index);
	void resign();
};

