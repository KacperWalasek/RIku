#pragma once
#include <string>

enum class InvitationState 
{
	Pending,
	Accepted,
	Joined
};
struct Invitation
{
	Invitation(std::string ip, std::string name)
		: ip(ip), name(name), state(InvitationState::Pending) {}
	std::string ip;
	std::string name;
	InvitationState state;
};