#pragma once
#include <map>
#include "IWinCondition.h"
#include "../Assets/AssetData.h"
#include "OnlyOneSurvived.h"
#include "EnoughResourceOfType.h"
#include "EnoughUnitsWithName.h"
#include "CombinedWinCondition.h"

class WinConditionFactory 
{
public:
	std::shared_ptr<IWinCondition> createWincondition(const logic::Asset& asset)
	{
		std::shared_ptr<IWinCondition> winCondition = nullptr;
		for (const auto& condition : asset.getMap())
		{
			auto c = createWincondition(condition.first, condition.second.asMap());
			if (c) winCondition = winCondition ? std::make_shared<CombinedWinCondition>(winCondition, c) : c;
		}
		return winCondition;
	}
	std::shared_ptr<IWinCondition> createWincondition(std::string type, std::map<std::string, logic::AssetData> data)
	{
		if (type == "only_one_survived")
			return std::make_shared<OnlyOneSurvived>();
		if (type == "enough_resources")
		{
			std::string resourceName = data.at("name").asString();
			int count = data.at("count").asInt();
			return std::make_shared<EnoughResourceOfType>(count, resourceName);
		}
		if (type == "enough_units")
		{
			std::string resourceName = "";
			if (data.find("name") != data.end())
				resourceName = data.at("name").asString();
			int count = data.at("count").asInt();
			return std::make_shared<EnoughUnitsWithName>(count, resourceName);
		}
		return nullptr;
	}


};