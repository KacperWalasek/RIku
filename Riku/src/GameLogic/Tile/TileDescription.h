#pragma once
#include <string>
#include <utility>
class TileDescription
{
public:
	TileDescription(int height, std::string biome, std::string ground, std::string area)
		: height(height), biome(std::move(biome)), ground(std::move(ground)), area(std::move(area)) {}
	int height;
	std::string biome, ground, area;
};

