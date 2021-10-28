//
// Created by kamil-hp on 15.10.2021.
//

#ifndef MAIN_CPP_ASSET_H
#define MAIN_CPP_ASSET_H
#include <map>
#include <variant>
#include <any>
#include <optional>
#include <vector>
#include <string>
#include "sol/sol.hpp"

namespace logic {

enum class AssetDataType {
	null=0,
	boolean=1,
	number=2,
	string=3,
	vector=4,
	map=5
};

class AssetData {
private:
	std::variant<std::nullptr_t, bool, double, std::string, std::vector<AssetData>, std::map<std::string, AssetData> > data;
public:
	AssetData(const AssetData& other) = default;
	AssetData(): data(nullptr) {}
	AssetData(bool a): data(a) {}
	AssetData(double a): data(a) {}
	AssetData(const std::string& a): data(a) {}
	AssetData(std::vector<AssetData>& v): data(v) {}
	AssetData(std::map<std::string, AssetData>& m): data(m) {}
	//operator =
	AssetData& operator=(const AssetData& a) = default;
	AssetData& operator=(AssetData&& a) noexcept {this->data=a.data;return *this;}
	AssetData& operator=(bool s) {this->data=s;return *this;}
	AssetData& operator=(double s) {this->data=s;return *this;}
	AssetData& operator=(const std::string& s) {this->data=s;return *this;}
	AssetData& operator=(std::vector<AssetData>&& s) {this->data=s;return *this;}
	AssetData& operator=(std::map<std::string, AssetData>&& s) {this->data=s;return *this;}
	//set
	void setNull() {data=nullptr;}
	[[nodiscard]] const auto& getData() const {return data;}
	[[nodiscard]] AssetDataType getType() const {return AssetDataType(data.index());}
	[[nodiscard]] bool isNull () const {return getType()==AssetDataType::null;}
	[[nodiscard]] bool asBool(bool defaultValue) const;
	[[nodiscard]] double asNumber(double defaultValue=nan("")) const;
	[[nodiscard]] std::string asString(const std::string& defaultValue="", bool areNumbersConverted=true) const;
	std::vector<AssetData>& asVector();
	[[nodiscard]] const std::vector<AssetData>& asVector() const;
	std::map<std::string, AssetData>& asMap();
	[[nodiscard]] const std::map<std::string, AssetData>& asMap() const;
	//array
	AssetData& operator[] (size_t i);
	const AssetData& operator[] (size_t i) const;
	//map
	AssetData& operator[] (const std::string& key);
	const AssetData& operator[] (const std::string& key) const;
};

class Asset {
	sol::state lua;
	std::string name;
	std::string parent_name;
	std::string type;
	std::string path;
	bool abstract=false;
	void updateFromParent(const Asset& parent);
	std::map<std::string, AssetData> data;
	std::map<std::string, sol::function> functions;
	friend class AssetHandler;
public:
	Asset(const std::string& path, const std::string& fileName) { load(path, fileName);}
	Asset()=default;
	Asset& operator=(Asset&& other) noexcept;
	void load(const std::string& path, const std::string& fileName);
	[[nodiscard]] const std::string& getName() const {return name;}
	[[nodiscard]] const std::string& getType() const {return type;}
	[[nodiscard]] const std::string& getPath() const {return path;}
	[[nodiscard]] bool isAbstract() const {return abstract;}

	[[nodiscard]] bool hasData(const std::string& key) const {return data.find(key)!=data.end();}
	[[nodiscard]] const std::map<std::string, AssetData>& getMap() const {return data;}
	[[nodiscard]] const AssetData& getByKey(const std::string& key) const {return !hasData(key) ? AssetData() : data.at(key);}

	bool hasFunction(const std::string& key) {return functions.find(key)!=functions.end();}
	[[nodiscard]] const std::map<std::string, sol::function>& getFunctions() const {return functions;}
	sol::function& getFunction(const std::string& key) {return functions[key];}
	[[nodiscard]] const sol::function& getFunction(const std::string& key) const {return functions.at(key);}
};

class AssetHandler {
private:
	std::map<std::string, std::vector<Asset*> > childrenNodes;
	void traverse(Asset* assetPtr);
	void passFile(const std::string& path, const std::string& fileName);
	//root name
public:
	std::map<std::string, Asset> assetNodes;
	void resolve();
	void findFiles(const std::string& path);
	//Asset& getRoot() {return *assetNodes["root"];}

};

}

#endif //MAIN_CPP_ASSET_H
