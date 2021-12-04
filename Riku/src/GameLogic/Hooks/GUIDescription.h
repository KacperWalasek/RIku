#pragma once
#include <string>
#include <vector>
#include <map>
#include "../Assets/Asset.h"
#include "../StateUpdate/Move/IMove.h"

class GUIDescription
{
	const std::map<std::string, sol::function>& funcs;
	std::string name;
	std::vector<std::map<std::string, logic::AssetData>> options;
public:
	GUIDescription(const std::map<std::string, sol::function>& funcs);
	GUIDescription(const GUIDescription& description);
	GUIDescription& operator=(const GUIDescription& desc) {
		this->name = desc.name;
		this->options = desc.options;
		return *this;
	}
	GUIDescription(const std::map<std::string, logic::AssetData>& asset, const std::map<std::string, sol::function>& funcs);
	std::string getName() const;
	std::vector<std::string> getOptions() const;
	std::shared_ptr<IMove> onOptionChosen(int index, const LogicAssets& assets) const;
};

