#pragma once
#include "../LogicAssets.h"

struct DeserializationData
{
	DeserializationData(const LogicAssets& assets) : assets(assets) {}
	const LogicAssets& assets;

};