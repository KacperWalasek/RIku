// Kacper Walasek
#pragma once
#include <string>
#include "AssetHandler.h"

class AssetUtils
{
public:
	template<typename T>
	static std::map<std::string,T> readNumericAsset(std::string name, logic::AssetHandler& handler)
	{
		auto assetOpt = handler.findAsset(name);
		if (!assetOpt.has_value())
			return {};
		std::map<std::string, logic::AssetData> asset = assetOpt.value().get().getMap();
		std::map<std::string, T> data = {};
		std::transform(asset.begin(), asset.end(),
			std::inserter(data,data.begin()),
			[](std::pair<std::string, logic::AssetData> record) {
				return std::pair<std::string,T>(record.first,T(record.first, record.second.asNumber()));
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

	static std::map<std::string, logic::Asset> getAllAssetsWithType(std::string type, logic::AssetHandler& handler)
	{
		std::map<std::string, logic::Asset> assetsWithType = {};
		std::copy_if(handler.assetNodes.begin(), handler.assetNodes.end(),
			std::inserter(assetsWithType, assetsWithType.end()),
			[type](const auto& nameAssetPair) {
				return nameAssetPair.second.getType() == type;
			});
		return assetsWithType;
	}
};

