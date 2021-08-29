// Kacper Walasek
#include "LogicResources.h"

void LogicResources::initialize()
{
	biomes = { {"Forest", 10}, {"Desert", 50}, {"Mountains", 30} };
	areas = { {"Wet", 2}, {"Dry", 1.2} };
	grounds = { {"Stone", 0.8}, {"Sand", 1.2}, {"Grass", 1} };
	playerResources = { { "Wood" }, { "Stone" }, { "Money" } };
}
