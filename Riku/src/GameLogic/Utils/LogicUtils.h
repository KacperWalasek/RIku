#pragma once
#include "../GameState.h"
#include "Path.h"
#include "ShortestPathEvaluator.h"
#include <queue>
class LogicUtils
{
	static unsigned int currentId;
	static unsigned int currentPlayerId;
	static int logicId;
	static std::map<std::string, std::shared_ptr<IHookable>> hookables;
	static std::queue<std::string> popups;
public:
	static void initialize(int logicId);
	static Path getShortestPath(
        const GameState& state, int fromX, int fromY, int toX, int toY, int movementPoints = 0);
	static std::string getUniqueId();
	static int getAvailablePlayerId(int count = 1);
	static void resetPlayerIndexes();
	//static std::string getPopup();
	//static void addPopup(std::string popup);

	static void addHookable(std::shared_ptr<IHookable> hookable);
	static void removeHookable(std::string id);
	static std::shared_ptr<IHookable> getHookable(std::string id);
	static void clearHookables();

	static Patch createPatchFromState(const GameState& state);
	static int getResponsePlayer(const GameState& state);
};

