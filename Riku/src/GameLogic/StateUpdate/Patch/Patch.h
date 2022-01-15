//Kacper Walasek
#pragma once
#include <vector>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include "PlayerPatch.h"
#include "TilePatch.h"
#include "RegisterHookablePatch.h"
#include "UnitPatch.h"
#include "MiniGamePatch.h"
#include "../../Tile/TileDescription.h"

class Patch
{
public:
	Patch() {};
	Patch(bool clearGameState) : clearGameState(clearGameState) {};
	Patch(PlayerPatch playerPatch) {
		playerPatches.insert({ playerPatch.player, playerPatch });
	}
	Patch(UnitPatch unitPatch) {
		unitPatches.insert({ unitPatch.unit, unitPatch });
	}
	Patch(TilePatch tilePatch) {
		tilePatches.insert({ tilePatch.tile, tilePatch });
	}
	Patch(RegisterHookablePatch registerHookablePatch) {
		registerHookablePatches.insert({ registerHookablePatch.id, registerHookablePatch });
	}
	Patch(MiniGamePatch miniGamePatch) {
		miniGamePatches.emplace(miniGamePatch.player, miniGamePatch);
	}
	Patch(int playerOnMove) : playerOnMove(playerOnMove){}
	Patch(const std::vector<std::vector<Tile>>& map)
	{
		for (const std::vector<Tile>& row : map)
		{
			std::vector<TileDescription> descRow;
			for (const Tile& tile : row)
				descRow.push_back(TileDescription(tile));
			this->map.push_back(descRow);
		}
	}


	std::map<int,PlayerPatch> playerPatches;
	std::map<std::pair<int,int>, TilePatch> tilePatches;
	std::map<std::string, RegisterHookablePatch> registerHookablePatches;
	std::map<std::string, UnitPatch> unitPatches;
	std::map<int, MiniGamePatch> miniGamePatches;
	std::vector<std::vector<TileDescription>>  map;
	bool clearGameState = false;
	int playerOnMove = -1;
	int playerCount = -1;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(playerOnMove, registerHookablePatches, playerPatches,
			tilePatches, unitPatches, miniGamePatches, map, clearGameState, playerCount);
	}

	friend Patch operator+(Patch p1, const Patch& p2)
	{
		if (p2.clearGameState)
		{
			p1.playerOnMove = -1;
			p1.map.clear();
			p1.playerPatches = {};
			p1.tilePatches = {};
			p1.registerHookablePatches = {};
			p1.unitPatches = {};
			p1.miniGamePatches = {};
			p1.clearGameState = true;
			p1.playerCount = -1;
		}
		// TODO upiekszyc to jakosc. Przeniesc fora do oddzielnej funkcji i wywolywac ja 5 razy czy cos
		for (auto plPatch2 : p2.playerPatches)
		{
			auto plPatch1 = p1.playerPatches.find(plPatch2.first);
			if (plPatch1 != p1.playerPatches.end())
				plPatch1->second += plPatch2.second;
			else
				p1.playerPatches.insert({ plPatch2 });
		}
		for (auto tilePatch2 : p2.tilePatches)
		{
			auto tilePatch1 = p1.tilePatches.find(tilePatch2.first);
			if (tilePatch1 != p1.tilePatches.end())
				tilePatch1->second += tilePatch2.second;
			else
				p1.tilePatches.insert({ tilePatch2 });
		}
		for (auto registerPatch2 : p2.registerHookablePatches)
		{
			auto registerPatch1 = p1.registerHookablePatches.find(registerPatch2.first);
			if (registerPatch1 != p1.registerHookablePatches.end())
				registerPatch1->second += registerPatch2.second;
			else
				p1.registerHookablePatches.insert({ registerPatch2 });
		}
		for (auto unitPatch2 : p2.unitPatches)
		{
			auto unitPatch1 = p1.unitPatches.find(unitPatch2.first);
			if (unitPatch1 != p1.unitPatches.end())
				unitPatch1->second += unitPatch2.second;
			else
				p1.unitPatches.insert({ unitPatch2 });
		}
		for (auto miniGamePatch2 : p2.miniGamePatches)
		{
			auto miniGamePatch1 = p1.miniGamePatches.find(miniGamePatch2.first);
			if (miniGamePatch1 != p1.miniGamePatches.end())
				miniGamePatch1->second += miniGamePatch2.second;
			else
				p1.miniGamePatches.insert({ miniGamePatch2 });
		}
		if (p2.playerOnMove != -1)
			p1.playerOnMove = p2.playerOnMove;
		if (p2.map.size() != 0)
			p1.map = p2.map;
		if (p2.playerCount > 0)
			p1.playerCount = p2.playerCount;
		return std::move(p1);
	}
};

