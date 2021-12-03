//
// Created by kamil-hp on 30.11.2021.
//
#include "JsonUtil.h"

Json::Value getJsonFromFile(const std::string& path, bool showNotFoundAsError) {
	Json::Value root;
	std::ifstream file(path);
	if(!file.good())
	{
		if(showNotFoundAsError)
			std::cerr << path << " not found!\n";
		else
			std::cout << path << " not found\n";
		return {};
	}
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, file, &root, &errs)) {
		std::cerr << path << " loading errors:\n";
		std::cerr << errs << '\n';
		return {};
	}
	std::cout << path << " loaded successfully\n";
	return root;
}