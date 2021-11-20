// Kacper Walasek
#pragma once
#include <string>

class IMoveDescription {
public:
	virtual std::string getMoveType() const = 0; 
};