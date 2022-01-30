#include "GUIDescription.h"
#include "MoveWrapper.h"

GUIDescription::GUIDescription(const std::map<std::string, sol::function>& funcs)
	: funcs(funcs)
{}

GUIDescription::GUIDescription(const GUIDescription & description)
	: name(description.name), funcs(description.funcs), options(description.options), headers(description.headers)
{}

GUIDescription::GUIDescription(const std::map<std::string,logic::AssetData>& gui, const std::map<std::string, sol::function>& funcs)
	:funcs(funcs)
{
	name = gui.at("name").asString();
	auto headerVec = gui.at("headers").asVector();
	for (const auto& header : headerVec)
		headers.push_back(header.asString());
	auto map = gui.at("options").asVector();
	for (const auto& option : map)
		options.push_back(option.asMap());
}

std::string GUIDescription::getName() const
{
	return name;
}

std::vector<std::vector<std::string>> GUIDescription::getOptions() const
{
	auto onOptionShow = funcs.find("onOptionShow");
	std::vector<std::vector<std::string>> descs;
	if (onOptionShow != funcs.end())
		std::transform(options.begin(), options.end(),
			std::back_inserter(descs),
			[&](std::map<std::string, logic::AssetData> map) {
				sol::variadic_results table = onOptionShow->second(map);
				std::vector<std::string> options;
				for (const auto& opt : table)
					options.push_back(opt.as<std::string>());
				return options;
			});
	return descs;
}

std::vector<std::string> GUIDescription::getHeaders() const
{
	return headers;
}

std::shared_ptr<IMove> GUIDescription::onOptionChosen(int index, int mapX, int mapY) const
{
	auto onOptionChosenFunc = funcs.find("onOptionChosen");
	if (options.size() > index && onOptionChosenFunc != funcs.end())
	{
		MoveWrapper wrapper = onOptionChosenFunc->second(options[index],mapX,mapY);
		return wrapper.move;
	}
	return std::shared_ptr<IMove>();
}

