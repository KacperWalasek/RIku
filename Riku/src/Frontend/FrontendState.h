#pragma once
#include <vector>
#include "../GameLogic/Tile/Tile.h"
#include "../GameLogic/GameLogic.h"

class FrontendState
{
	GameLogic& logic;
public:
	FrontendState(GameLogic& logic);

	const std::vector<std::vector<Tile>>& getMap();
	std::map<std::string, int> getResources();
	std::vector<std::string> getAvailableBuildings(int mapX, int mapY);
	std::vector<std::shared_ptr<const Unit>> getUnits();

	void build(std::string name, int mapX, int mapY);
	void moveUnit(int fromX, int fromY, int toX, int toY);
	void finishTurn();
};

