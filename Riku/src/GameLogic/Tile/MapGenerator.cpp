#include "MapGenerator.h"

MapGenerator::MapGenerator(logic::Asset asset)
	: asset(asset)
{}

std::vector<std::vector<Tile>> MapGenerator::getMap(const LogicAssets& assets)
{
	auto tileDescriptions = assets.mapGenerator.getFunction("onCreateMap")().get<std::vector<std::vector<TileDescription>>>();
	std::vector<std::vector<Tile>> tiles;
	std::transform(tileDescriptions.begin(), tileDescriptions.end(),
			std::back_insert_iterator(tiles),
			[&assets](const auto& row) {
				std::vector<Tile> tileRow;
				std::transform(row.begin(), row.end(), std::back_insert_iterator(tileRow),
					[&assets](const TileDescription& descr) {
						return Tile(descr.height,assets.areas.at(descr.area), assets.grounds.at(descr.ground), assets.biomes.at(descr.biome));
					});
				return tileRow;
			}
		);
	return std::move(tiles);
}
