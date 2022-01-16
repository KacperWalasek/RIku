#pragma once
#include <string>
#include <cereal/access.hpp>
class TileDescription
{
public:
	TileDescription() : height(0), biome(""), ground(""), area(""), tileObject("") {}
	TileDescription(int height, std::string biome, std::string ground, std::string area, std::string tileObject = "")
		: height(height), biome(biome), area(area), ground(ground), tileObject(tileObject) {}
	TileDescription(const Tile& tile)
		: height(tile.height), biome(tile.biome.getName()), area(tile.area.getName()), ground(tile.ground.getName()) {}
	int height;
	std::string biome, ground, area;
	std::string tileObject;
	
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(height, biome, ground, area, tileObject);
	}
};

