//
// Created by kamil-hp on 15.10.2021.
//

#include "Asset.h"

#include <memory>
#include <filesystem>

namespace logic {

std::map<std::string, AssetData> getData(const sol::table& table) {
	std::map<std::string, AssetData> data;
	for(const std::pair<sol::object,sol::object>& v: table) {
		std::string key = v.first.as<std::string>();
		auto& value = v.second;
		switch(value.get_type()) {
			case sol::type::nil:
			case sol::type::none:
				data[key] = AssetData();
				break;
			case sol::type::boolean:
				data[key] = value.as<bool>();
				break;
			case sol::type::string:
				data[key] = value.as<std::string>();
				break;
			case sol::type::number:
				data[key] = value.as<double>();
				break;
			case sol::type::table: {
				auto readTable = getData(value.as<sol::table>());
				data[key] = std::map<std::string, AssetData>();
				for (const auto &v: readTable) {
					data[key][v.first] = v.second;
				}
			}
				break;
			case sol::type::lightuserdata:
			case sol::type::userdata:
				std::cout << "User data is not allowed here.\n";
				break;
				//ignored data types:
			case sol::type::function:
			case sol::type::thread:
			case sol::type::poly:
				break;
		}
	}
	return data;
}

//AssetData

bool AssetData::asBool(bool defaultValue) const {
	if(getType()==AssetDataType::boolean)
		return std::get<bool>(data);
	return defaultValue;
}
double AssetData::asNumber(double defaultValue) const {
	if(getType()==AssetDataType::number)
		return std::get<double>(data);
	return defaultValue;
}
std::string AssetData::asString(const std::string& defaultValue, bool areNumbersConverted) const {
	if(getType()==AssetDataType::string)
		return std::get<std::string>(data);
	else if(areNumbersConverted && getType()==AssetDataType::boolean)
		return std::to_string(std::get<bool>(data));
	else if(areNumbersConverted && getType()==AssetDataType::number)
		return std::to_string(std::get<double>(data));
	return defaultValue;
}
std::vector<AssetData>& AssetData::asVector() {
	if(getType()==AssetDataType::vector)
		return std::get<std::vector<AssetData> >(data);
	throw std::invalid_argument("Not a vector");
}
const std::vector<AssetData>& AssetData::asVector() const {
	if(getType()==AssetDataType::vector)
		return std::get<std::vector<AssetData> >(data);
	throw std::invalid_argument("Not a vector");
}
std::map<std::string, AssetData>& AssetData::asMap() {
	if(getType()==AssetDataType::map)
		return std::get<std::map<std::string, AssetData> >(data);
	throw std::invalid_argument("Not a map");
}
const std::map<std::string, AssetData>& AssetData::asMap() const {
	if(getType()==AssetDataType::map)
		return std::get<std::map<std::string, AssetData> >(data);
	throw std::invalid_argument("Not a map");
}
AssetData& AssetData::operator[] (size_t i) {
	auto& vec = asVector();
	if(i>=0 || i<vec.size())
		return vec[i];
	throw std::out_of_range("Out of range");
}
const AssetData& AssetData::operator[] (size_t i) const {
	auto& vec = asVector();
	if(i>=0 || i<vec.size())
		return vec[i];
	throw std::out_of_range("Out of range");
}
AssetData& AssetData::operator[] (const std::string& key) {
	auto& map = asMap();
	return map[key];
}
const AssetData& AssetData::operator[] (const std::string& key) const {
	auto& map = asMap();
	return map.at(key);
}

//Asset

void Asset::load(const std::string& path, const std::string& fileName) {
	this->path = path;
	lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::io);
	lua.script_file(path+"/"+fileName);

	type = lua["asset_type"];
	//get name from file
	sol::optional<std::string> pn = lua["name"];
	if(pn.has_value())
		name=*pn;
	else
		name=type;
	//get parent name from file
	sol::optional<std::string> op = lua["parent"];
	if(op.has_value())
		parent_name=*op;
	else if(name != type)
		parent_name = type; //direct child of asset type object
	else if (name != "root")
		parent_name = "root"; //it is root of asset type
	else
		parent_name = ""; //it is root
	//get is abstract name from file
	sol::optional<bool> ab = lua["is_abstract"];
	if(ab.has_value())
		abstract = *ab;
	else {
		abstract = (name == type) || (name == "root");
	}
	sol::table parameterTable = lua[type];
	data = getData(parameterTable);
	//load functions
	for(const auto& v: lua) {
		auto key = v.first.as<std::string>();
		if(v.second.get_type() == sol::type::function) {
			//it is a function
			functions[key] = v.second.as<sol::function>();
		}
	}
}


Asset& Asset::operator=(Asset&& other) noexcept {
	this->name = other.name;
	this->parent_name = other.parent_name;
	this->type = other.type;
	this->abstract = other.abstract;
	this->data = std::move(other.data);
	return *this;
}

void Asset::actualizeFromParent(const Asset& parent) {
	for(const auto& d: parent.data) {
		auto& key = d.first;
		auto& value = d.second;
		if(data.find(key)==data.end()) {
			//key is not in data yet
			data[key]=value;
		}
	}
	for(const auto& f: parent.functions) {
		const std::string& key = f.first;
		auto& value = f.second;
		if(functions.find(key)==functions.end()) {
			//key is not in data yet
			functions[key]=value;
		}
		else {
			//using parent function as "_{parent_name}_{function_name}
			if(key[0]=='_') //already derived function
				functions[key]=value;
			else
				functions["_"+parent_name+"_"+key]=value;
		}
	}
}

//AssetHandler

void AssetHandler::passFile(const std::string& path, const std::string& fileName) {
	Asset newAsset(path, fileName);
	std::string assetName = newAsset.name;
	std::string assetParent = newAsset.parent_name;
	assetNodes[newAsset.name] = std::move(newAsset);
	if(assetName!="root") {
		Asset* assetPtr=&assetNodes[assetName];
		if(assetNodes.find(assetParent)==assetNodes.end())
			childrenNodes[assetParent]=std::vector({assetPtr});
		else
			childrenNodes[assetParent].push_back(assetPtr);
	}
}

void AssetHandler::traverse(Asset* assetPtr) {
	if(assetPtr==nullptr)
		return;
	std::vector<Asset*> children = childrenNodes[assetPtr->getName()];
	for(Asset* child: children) {
		if(child==nullptr)
			continue;
		child->actualizeFromParent(*assetPtr);
		traverse(child);
	}
}

void AssetHandler::resolve() {
	traverse(&assetNodes["root"]);
}

void AssetHandler::findFiles(const std::string& path) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if(entry.is_directory()) {
			//it is asset
			std::string path2 = entry.path().string()+"/script.lua";
			if(std::filesystem::exists(path2)) {
				std::cout << "Loading asset " << std::filesystem::relative(entry.path(), path) << "\n";
				passFile(entry.path(), "script.lua");
			}
			else
				std::cerr << entry.path() << " is not a valid asset\n";
		}
	}
	resolve();
}

}
