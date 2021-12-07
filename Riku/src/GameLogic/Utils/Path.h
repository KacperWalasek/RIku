#pragma once
#include <vector>
struct Path
{
	Path(std::vector<std::pair<int, int>> path, int cost)
		: cost(cost), path(path) {}
	std::vector<std::pair<int, int>> path;
	int cost;
};

