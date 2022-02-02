#pragma once
#include "../StateUpdate/Patch/Patch.h"
#include <cereal/types/vector.hpp>
struct SaveStruct
{
	SaveStruct() {}
	SaveStruct(Patch patch, std::map<std::string, Invitation> invitations, int hotseatCount) : patch(patch), hotseatCount(hotseatCount)
	{
		for (const auto& pair : invitations)
			this->invitations.push_back(Invitation(pair.first, pair.second.name, pair.second.hotseatCount, InvitationState::Loaded, pair.second.id));
	}
	Patch patch;
	std::vector<Invitation> invitations;
	int hotseatCount;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(patch, invitations, hotseatCount);
	}

};

