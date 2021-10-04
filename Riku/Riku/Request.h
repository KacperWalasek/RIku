#pragma once
#include <string>

class Request
{
	std::string key;
public:
	Request(std::string key);
	std::string getKey() const;
};

