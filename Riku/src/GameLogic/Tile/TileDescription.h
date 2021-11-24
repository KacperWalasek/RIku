#pragma once
#include <string>
class TileDescription
{
public:
	TileDescription(int height, std::string biome, std::string ground, std::string area)
		: height(height), biome(biome), area(area), ground(ground) {}
	int height;
	std::string biome, ground, area;
};

