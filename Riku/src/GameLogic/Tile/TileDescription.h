#pragma once
#include <string>
class TileDescription
{
public:
	TileDescription(int height, std::string biome, std::string ground, std::string area, std::string tileObject = "")
		: height(height), biome(biome), area(area), ground(ground), tileObject(tileObject) {}
	int height;
	std::string biome, ground, area;
	std::string tileObject;
};

