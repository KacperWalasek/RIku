//
// Created by kamil-hp on 06.09.2021.
//
#include "Config.h"
#include "JsonUtil.h"
#include <fstream>
#include <iostream>

constexpr char FRONTEND_CONFIG_PATH[]="../frontend_config.json";

bool front::Config::load() {
	Json::Value root = getJsonFromFile(FRONTEND_CONFIG_PATH);
	if(root.isNull())
		return EXIT_FAILURE;
	screenWidth = root.get("screen_width",800).asInt();
	screenHeight = root.get("screen_height",600).asInt();
	isFullscreen = root.get("is_fullscreen",false).asBool();
	angle = root.get("angle",80.f).asFloat();
	fov = root.get("fov",45.f).asFloat();
	maxZoomHeight=root.get("max_zoom_height",60.f).asFloat();
	minZoomHeight=root.get("min_zoom_height",3.f).asFloat();
	language=root.get("language","en").asString();
	return EXIT_SUCCESS;
}

bool front::Config::save() const {
	Json::Value root;
	root["screen_width"]=screenWidth;
	root["screen_height"]=screenHeight;
	root["is_fullscreen"]=isFullscreen;
	root["angle"]=angle;
	root["fov"]=fov;
	root["max_zoom_height"]=maxZoomHeight;
	root["min_zoom_height"]=minZoomHeight;
	root["language"]=language;
	std::ofstream file(FRONTEND_CONFIG_PATH);
	if(!file.good())
	{
		std::cerr << "ERROR: " << FRONTEND_CONFIG_PATH << " cannot be created or used!\n";
		return EXIT_FAILURE;
	}
	file << root << '\n';
	file.close();
	std::cout << FRONTEND_CONFIG_PATH << " saved successfully\n";
	return EXIT_SUCCESS;
}