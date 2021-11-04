// Kacper Walasek
#pragma once
#include <string>
#include "AssetHandler.h"
class AssetUtils
{
public:
	template<typename T>
	static std::vector<T> readNumericAsset(std::string name, logic::AssetHandler& handler)
	{
		auto assetOpt = handler.findAsset(name);
		if (!assetOpt.has_value())
			return {};
		std::map<std::string, logic::AssetData> asset = assetOpt.value().get().getMap();
		std::vector<T> data = {};
		std::transform(asset.begin(), asset.end(),
			std::back_insert_iterator<std::vector<T>>(data),
			[](std::pair<std::string, logic::AssetData> record) {
				return T(record.first, record.second.asNumber());
			});
		return data;
	}

	template<typename T>
	static std::vector<T> readStringArray(std::string name, logic::AssetHandler& handler)
	{
		auto assetOpt = handler.findAsset(name);
		if (!assetOpt.has_value())
			return {};
		std::map<std::string, logic::AssetData> asset = assetOpt.value().get().getMap();
		std::vector<T> data = {};
		std::transform(asset.begin(), asset.end(),
			std::back_insert_iterator<std::vector<T>>(data),
			[](std::pair<std::string, logic::AssetData> record) {
				return T(record.second.asString());
			});
		return data;
	}
};

