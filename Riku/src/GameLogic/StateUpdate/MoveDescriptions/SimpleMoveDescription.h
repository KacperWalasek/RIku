// Kacper Walasek
#pragma once
#include <string>
#include "IMoveDescription.h"

class SimpleMoveDescription : public IMoveDescription {
	std::string type;
public:
	SimpleMoveDescription(std::string type) : type(type) {}
	std::string getMoveType() const override { return type; }
};