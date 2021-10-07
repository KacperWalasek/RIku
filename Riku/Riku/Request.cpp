#include "Request.h"

Request::Request(std::string key):key(key)
{}

std::string Request::getKey() const
{
	return key;
}
