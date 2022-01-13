#pragma once
#include "../LogicAssets.h"
#include "../../MiniGame/MiniGameAssets.h"

struct DeserializationData
{
	DeserializationData(const LogicAssets& assets, const minigame::MiniGameAssets& miniGameAssets) 
		: assets(assets), miniGameAssets(miniGameAssets){}
	const LogicAssets& assets;
	const minigame::MiniGameAssets& miniGameAssets;

};