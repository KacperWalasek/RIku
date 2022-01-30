#include "MapGenerator.h"
#include "../StateUpdate/Move/BuildTileObject.h"
#include "../GameObject/SimpleTileObject.h"

MapGenerator::MapGenerator(logic::Asset asset)
	: asset(asset)
{}

std::vector<std::vector<Tile>> MapGenerator::getMap(const LogicAssets& assets)
{
	std::cout << "began generation\n";
	auto tileDescriptions = assets.mapGenerator.getFunction("onCreateMap")().get<std::vector<std::vector<TileDescription>>>();
	std::cout << "finished generation\n";
	std::vector<std::vector<Tile>> tiles;
	std::transform(tileDescriptions.begin(), tileDescriptions.end(),
			std::back_insert_iterator(tiles),
			[&assets](const auto& row) {
				std::vector<Tile> tileRow;
				std::transform(row.begin(), row.end(), std::back_insert_iterator(tileRow),
					[&assets](const TileDescription& descr) {
						Tile tile(descr.height, assets.areas.at(descr.area), assets.grounds.at(descr.ground), assets.biomes.at(descr.biome));
						auto assetIt = assets.tileObjects.find(descr.tileObject);
						if (assetIt != assets.tileObjects.end())
						{
							const logic::Asset& asset = assetIt->second;
							tile.object = std::make_shared<SimpleTileObject>(descr.tileObject, -1, asset.getFunctions(), GUIDescription(asset.getFunctions()));
						}
						return tile;
					});
				return tileRow;
			}
		);
	return std::move(tiles);
}
