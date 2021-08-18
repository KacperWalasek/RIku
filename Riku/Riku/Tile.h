// Kacper Walasek
#pragma once
#include <memory>
#include "Area.h"
#include "Ground.h"
#include "Biome.h"

class Tile
{
public:
	Tile(int height, const Area& area, const Ground& ground, const Biome& biome);

	int height;
	const Area& area;
	const Ground& ground;
	const Biome& biome;

	double getCost() const;

	/*
		TODO:
		- Resource
		- Tile Object
	*/
};

