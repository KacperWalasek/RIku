#pragma once
#include <string>
#include <cereal/types/string.hpp>

enum class InvitationState 
{
	Loaded,
	Pending,
	Accepted,
	Joined
};
struct Invitation
{
	Invitation() {}
	Invitation(std::string ip, std::string name)
		: ip(ip), name(name), state(InvitationState::Pending) {}
	Invitation(std::string ip, std::string name, int hotseatCount, InvitationState state)
		: ip(ip), name(name), hotseatCount(hotseatCount), state(state) {}
	std::string ip;
	std::string name;
	InvitationState state;
	int hotseatCount = 1;
	std::string GetStateAsString() const {
		switch (state)
		{
		case InvitationState::Pending: return "Pending";
		case InvitationState::Accepted: return "Accepted";
		case InvitationState::Joined: return "Joined";
		default: return "";
		}
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(ip, name, state, hotseatCount);
	}

};