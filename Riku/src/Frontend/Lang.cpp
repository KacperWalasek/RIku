//
// Created by kamil-hp on 30.11.2021.
//
#include "Lang.h"
#include "JsonUtil.h"
#include "../GameLogic/Assets/AssetHandler.h"
std::map<std::string, std::string> front::Lang::texts;

bool front::Lang::loadLanguage(const logic::AssetHandler &handler, const std::string& langName) {
	std::cout << "\nLoading language " << langName << ":\n";
	//load text
	auto root = getJsonFromFile("../lang/"+langName+".json");
	if(root.isNull())
		return false;
	texts.clear();
	for(const auto& key: root.getMemberNames()) {
		texts[key]=root.get(key,key).asString();
	}
	//from assets
	for(const auto& node: handler.assetNodes) {
		root = getJsonFromFile(node.second.getPath()+"/lan.json",false);
		if(root.isNull())
			continue;
		if(root.isMember(langName))
			root=root[langName];
		else if(root.isMember("en"))
			root=root["en"];
		else
			continue;
		for(const auto& key: root.getMemberNames()) {
			texts[key]=root.get(key,texts[key]).asString();
		}
	}
	std::cout << "Language " << langName << " loaded successfully\n\n";
	return true;
}

const std::string& front::Lang::get(const std::string &name) {
	if(texts.find(name)!=texts.end())
		return texts[name];
	return name;
}

const char *front::Lang::get(const char *name) {
	if(texts.find(name)!=texts.end())
		return texts[name].c_str();
	return name;
}

const unsigned char* front::Lang::getUtf(const char* name) {
	return (unsigned char*)get(name);
}

const unsigned char* front::Lang::getUtf(const std::string& name) {
	return getUtf(name.c_str());
}
