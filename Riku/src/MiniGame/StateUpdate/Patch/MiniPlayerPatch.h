#pragma once
class MiniPlayerPatch
{
public:
	MiniPlayerPatch() {};
	MiniPlayerPatch(std::shared_ptr<MiniUnit> added) { addedUnits.push_back(added); }
	std::vector<std::shared_ptr<MiniUnit>> addedUnits;
	MiniPlayerPatch& operator+=(const MiniPlayerPatch& patch)
	{
		auto units = patch.addedUnits;
		if (units.size() > 0)
			addedUnits.insert(addedUnits.end(), units.begin(), units.end());
		return *this;
	}
};

