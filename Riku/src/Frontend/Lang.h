//
// Created by kamil-hp on 30.11.2021.
//

#ifndef RIKU_LANG_H
#define RIKU_LANG_H

#include <map>
#include <string>
namespace logic {
	class AssetHandler;
}
namespace front {
	class Lang {
	private:
		static std::map<std::string, std::string> texts;

	public:
		static bool loadLanguage(const logic::AssetHandler &handler, const std::string &langName);
		static const std::string& get(const std::string& name);
		static const char* get(const char* name);
	};
}


#endif //RIKU_LANG_H
