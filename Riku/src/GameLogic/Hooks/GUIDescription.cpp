#include "GUIDescription.h"
#include "MoveWrapper.h"
#include "../LogicAssets.h"

GUIDescription::GUIDescription(const std::map<std::string, sol::function>& funcs)
	: funcs(funcs)
{}

GUIDescription::GUIDescription(const GUIDescription & description)
	: name(description.name), funcs(description.funcs), options(description.options)
{}

GUIDescription::GUIDescription(const std::map<std::string,logic::AssetData>& gui, const std::map<std::string, sol::function>& funcs)
	:funcs(funcs)
{
	name = gui.at("name").asString();
	auto map = gui.at("options").asVector();
	for (const auto& option : map)
		options.push_back(option.asMap());
}

std::string GUIDescription::getName() const
{
	return name;
}

std::vector<std::string> GUIDescription::getOptions() const
{
	std::vector<std::string> descs;
	std::transform(options.begin(), options.end(), 
		std::back_inserter(descs), 
		[](const std::map<std::string, logic::AssetData>& map){
			return map.at("name").asString();
		});
	return descs;
}

std::shared_ptr<IMove> GUIDescription::onOptionChosen(int index, const LogicAssets& assets) const
{
	auto onOptionChosenFunc = funcs.find("onOptionChosen");
	if (options.size() > index && onOptionChosenFunc != funcs.end())
	{
		MoveWrapper wrapper = onOptionChosenFunc->second(assets);
		return wrapper.move;
	}
	return std::shared_ptr<IMove>();
}
