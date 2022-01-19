#pragma once
#include <string>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
class InvitationAcceptance
{
public:
	InvitationAcceptance()
		: ip(), name(), hotseatCount() {}
	InvitationAcceptance(std::string ip, std::string name, std::string hash, int hotseatCount)
		: ip(ip), name(name), hash(hash), hotseatCount(hotseatCount) {}
	std::string ip;
	std::string name;
	std::string hash;
	int hotseatCount;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(ip, name, hash, hotseatCount);
	}

	std::string serialize()
	{
		std::stringstream ss;
		cereal::BinaryOutputArchive archive(ss);
		archive(*this);
		return ss.str();
	}

	void deserialize(std::string data)
	{
		std::stringstream ss(data);
		cereal::BinaryInputArchive archive(ss);
		archive(*this);
	}
};