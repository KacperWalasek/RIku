#include "AssetData.h"


namespace logic {

	bool AssetData::asBool(bool defaultValue) const {
		if (getType() == AssetDataType::boolean)
			return std::get<bool>(data);
		return defaultValue;
	}
	double AssetData::asNumber(double defaultValue) const {
		if (getType() == AssetDataType::number)
			return std::get<double>(data);
		return defaultValue;
	}
	int AssetData::asInt(int defaultValue) const {
		if (getType() == AssetDataType::number)
			return std::get<double>(data);
		return defaultValue;
	}
	std::string AssetData::asString(const std::string& defaultValue, bool areNumbersConverted) const {
		if (getType() == AssetDataType::string)
			return std::get<std::string>(data);
		else if (areNumbersConverted && getType() == AssetDataType::boolean)
			return std::to_string(std::get<bool>(data));
		else if (areNumbersConverted && getType() == AssetDataType::number)
		{
			double nr = std::get<double>(data);
			if (floor(nr) == nr)
				return std::to_string((int)nr);
			else
				return std::to_string(nr);
		}
		return defaultValue;
	}
	std::vector<AssetData>& AssetData::asVector() {
		if (getType() == AssetDataType::vector)
			return std::get<std::vector<AssetData> >(data);
		throw std::invalid_argument("Not a vector");
	}
	const std::vector<AssetData>& AssetData::asVector() const {
		if (getType() == AssetDataType::vector)
			return std::get<std::vector<AssetData> >(data);
		throw std::invalid_argument("Not a vector");
	}
	std::map<std::string, AssetData>& AssetData::asMap() {
		if (getType() == AssetDataType::map)
			return std::get<std::map<std::string, AssetData> >(data);
		throw std::invalid_argument("Not a map");
	}
	const std::map<std::string, AssetData>& AssetData::asMap() const {
		if (getType() == AssetDataType::map)
			return std::get<std::map<std::string, AssetData> >(data);
		throw std::invalid_argument("Not a map");
	}
	AssetData& AssetData::operator[] (size_t i) {
		auto& vec = asVector();
		if (i >= 0 || i < vec.size())
			return vec[i];
		throw std::out_of_range("Out of range");
	}
	const AssetData& AssetData::operator[] (size_t i) const {
		auto& vec = asVector();
		if (i >= 0 || i < vec.size())
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
}