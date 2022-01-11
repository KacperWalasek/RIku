//
// Created by kamil-hp on 15.10.2021.
//

#include "Asset.h"

#include <memory>
#include <filesystem>
#include <fstream>
#include <hash-library/sha256.h>
#include "../StateUpdate/Move/TestMove.h"
#include "../Hooks/MoveWrapper.h"
#include "../Tile/TileDescription.h"
#include "RandomWrapper.h"
#include "../StateUpdate/Move/CreateUnit.h"
#include "../StateUpdate/Move/CombinedMove.h"
#include "../StateUpdate/Move/UseResources.h"
#include <iostream>

namespace logic {

	std::map<std::string, AssetData> getData(const sol::table& table) {
		std::map<std::string, AssetData> data;
		for (const std::pair<sol::object, sol::object>& v : table) {
			std::string key = v.first.get_type() == sol::type::string ? v.first.as<std::string>() : std::to_string(v.first.as<int>());
			auto& value = v.second;
			switch (value.get_type()) {
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
				if (readTable.size() == 0)
				{
					data[key] = std::vector<AssetData>();
					break;
				}
				if (readTable.begin()->first == "1")
				{
					std::vector<AssetData> dataArray;
					std::transform(readTable.begin(), readTable.end(), std::back_insert_iterator(dataArray),
						[](std::pair<std::string, AssetData> record) {
							return record.second;
						});
					data[key] = dataArray;
				}
				else
					data[key] = readTable;
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

	void Asset::load(const std::string& path, const std::string& fileName) {
		lua = std::make_shared<sol::state>();
		this->path = path;
		//load file and calculate hash
		std::ifstream file(path + "/" + fileName);
		std::string fileContent(std::istreambuf_iterator<char>{file}, {});
		SHA256 sha;
		hash = sha(fileContent);
		file.close();
		//init lua
		lua->open_libraries(sol::lib::base, sol::lib::string, sol::lib::io, sol::lib::math, sol::lib::os);

		lua->new_usertype<logic::AssetData>("AssetData",
			sol::constructors<logic::AssetData(const logic::AssetData&)>(),
			"as_int", &logic::AssetData::asInt
			);
		lua->new_usertype<TestMove>("TestMove",
			sol::constructors<TestMove()>()
			);
		lua->new_usertype<CreateUnit>("CreateUnit",
			sol::constructors<CreateUnit(std::string,int,int)>()
			);
		lua->new_usertype<UseResources>("UseResources",
			sol::constructors<UseResources(int, int), UseResources(std::string, int)>()
			);
		lua->new_usertype<MoveWrapper>("MoveWrapper",
			sol::constructors<MoveWrapper(TestMove), MoveWrapper(CreateUnit), MoveWrapper(CombinedMove), MoveWrapper(UseResources)>()
			);
		lua->new_usertype<TileDescription>("TileDescription",
			sol::constructors<TileDescription(int,std::string,std::string,std::string)>()
			);
		lua->new_usertype<CombinedMove>("CombinedMove",
			sol::constructors<CombinedMove(MoveWrapper,MoveWrapper)>()
			);
		
		/*
		Na razie ten kod zostawiam, bo mo�e go b�d� u�ywa�
		auto factories = sol::factories([]() { return std::make_shared<TestMove>(); });
		lua->new_usertype< TestMove>("TestMove",
			sol::meta_function::construct, factories,
			sol::call_constructor, factories);*/
		auto load_result = lua->load(fileContent);
		if (!load_result.valid()) 
		{
			sol::error err = load_result;
			std::string what = err.what();
			std::cout << "error while loading " + (path + "/" + fileName) << " file" << std::endl;
			std::cout << "\t" << what << std::endl;
			return;
		}
		lua->script_file(path + "/" + fileName);


		type = (*lua)["asset_type"];
		//get name from file
		sol::optional<std::string> pn = (*lua)["name"];
		if (pn.has_value())
			name = *pn;
		else
			name = type;
		//get parent name from file
		sol::optional<std::string> op = (*lua)["parent"];
		if (op.has_value())
			parent_name = *op;
		else if (name != type)
			parent_name = type; //direct child of asset type object
		else if (name != "root")
			parent_name = "root"; //it is root of asset type
		else
			parent_name = ""; //it is root
		//get is abstract name from file
		sol::optional<bool> ab = (*lua)["is_abstract"];
		if (ab.has_value())
			abstract = *ab;
		else {
			abstract = (name == type) || (name == "root");
		}
		sol::table parameterTable = (*lua)[type];
		data = getData(parameterTable);
		//load functions
		for (const auto& v : lua->globals()) {
			auto key = v.first.as<std::string>();
			if (v.second.get_type() == sol::type::function && key.substr(0,2)=="on") {
				std::cout << std::boolalpha << "\t" << key << ": " << "valid=" << v.second.valid() << std::endl;
				//it is a function
				functions[key] = v.second.as<sol::function>();
			}
		}
	}


	Asset::Asset(const Asset& asset) 
		: lua(asset.lua), name(asset.name), parent_name(asset.parent_name), type(asset.type), path(asset.path),
		  hash(asset.hash), abstract(asset.abstract), data(asset.data), functions(asset.functions)
	{}

	Asset& Asset::operator=(Asset&& other) noexcept {
		this->lua = std::move(other.lua);
		this->name = other.name;
		this->parent_name = other.parent_name;
		this->type = other.type;
		this->path = std::move(other.path);
		this->hash = std::move(other.hash);
		this->abstract = other.abstract;
		this->data = std::move(other.data);
		this->functions = other.functions;
		return *this;
	}

	void Asset::updateFromParent(const Asset& parent) {
		for (const auto& d : parent.data) {
			auto& key = d.first;
			auto& value = d.second;
			if (data.find(key) == data.end()) {
				//key is not in data yet
				data[key] = value;
			}
		}
		for (const auto& f : parent.functions) {
			const std::string& key = f.first;
			auto& value = f.second;
			if (functions.find(key) == functions.end()) {
				//key is not in data yet
				functions[key] = value;
			}
			else {
				//using parent function as "_{parent_name}_{function_name}
				if (key[0] == '_') //already derived function
					functions[key] = value;
				else
					functions["_" + parent_name + "_" + key] = value;
			}
		}
	}
}
