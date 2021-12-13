// Kamil Boryczka
#pragma once
#include <map>
#include <variant>
#include <any>
#include <optional>
#include <vector>
#include <string>
#include "sol/sol.hpp"

namespace logic {

	enum class AssetDataType {
		null = 0,
		boolean = 1,
		number = 2,
		string = 3,
		vector = 4,
		map = 5
	};

	class AssetData {
	private:
		std::variant<std::nullptr_t, bool, double, std::string, std::vector<AssetData>, std::map<std::string, AssetData> > data;
	public:
		AssetData(const AssetData& other) = default;
		AssetData() : data(nullptr) {}
		AssetData(bool a) : data(a) {}
		AssetData(double a) : data(a) {}
		AssetData(const std::string& a) : data(a) {}
		AssetData(std::vector<AssetData>& v) : data(v) {}
		AssetData(std::map<std::string, AssetData>& m) : data(m) {}
		//operator =
		AssetData& operator=(const AssetData& a) = default;
		AssetData& operator=(AssetData&& a) noexcept { this->data = a.data; return *this; }
		AssetData& operator=(bool s) { this->data = s; return *this; }
		AssetData& operator=(double s) { this->data = s; return *this; }
		AssetData& operator=(const std::string& s) { this->data = s; return *this; }
		AssetData& operator=(std::vector<AssetData>&& s) { this->data = s; return *this; }
		AssetData& operator=(std::map<std::string, AssetData>&& s) { this->data = s; return *this; }
		//set
		void setNull() { data = nullptr; }
		[[nodiscard]] const auto& getData() const { return data; }
		[[nodiscard]] AssetDataType getType() const { return AssetDataType(data.index()); }
		[[nodiscard]] bool isNull() const { return getType() == AssetDataType::null; }
		[[nodiscard]] bool asBool(bool defaultValue) const;
		[[nodiscard]] double asNumber(double defaultValue = nan("")) const;
		[[nodiscard]] int asInt(int defaultValue = INT_MAX) const;
		[[nodiscard]] std::string asString(const std::string& defaultValue = "", bool areNumbersConverted = true) const;
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
}