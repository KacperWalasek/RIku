#pragma once
#include <vector>
struct Path
{
	Path(std::vector<std::pair<int, int>> path, int cost)
		: path(path), cost(cost) {}
	std::vector<std::pair<int, int>> path;
	int cost;
};

