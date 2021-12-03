//
// Created by kamil-hp on 30.11.2021.
//

#ifndef RIKU_JSONUTIL_H
#define RIKU_JSONUTIL_H
#ifdef __linux__
#include <jsoncpp/json/json.h>
#elif defined _WIN32
#include <json/json.h>
#endif // __linux__
#include <fstream>
#include <iostream>

Json::Value getJsonFromFile(const std::string& path, bool showNotFoundAsError=true);

#endif //RIKU_JSONUTIL_H
