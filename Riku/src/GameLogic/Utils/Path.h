#pragma once
#include <vector>

struct PathTile 
{
	PathTile(std::pair<int, int> tile, int cost, int available)
		: cost(cost), tile(tile), reachable(available >= cost) {}
	std::pair<int, int> tile;
	int cost;
	bool reachable;
};

struct Path
{
	Path(std::vector<PathTile> path, int cost)
		: cost(cost), path(path) 
	{
		for (reachableTilesNumber = 0; reachableTilesNumber < path.size(); reachableTilesNumber++)
			if (!path[reachableTilesNumber].reachable) 
				break;
	}
	std::vector<PathTile> path;
	int cost;
	int reachableTilesNumber;
};

