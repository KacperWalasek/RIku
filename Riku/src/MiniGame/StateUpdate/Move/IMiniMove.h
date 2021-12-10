//Kacper Walasek
#pragma once
#include <memory>

class MiniPatch;
class MiniGameState;
class MiniGameAssets;
class IMiniMove
{
public:
	virtual std::shared_ptr<MiniPatch> createPatch(const MiniGameState& state, const MiniGameAssets& assets) const = 0;
	virtual bool isDoable(const MiniGameState& state, const MiniGameAssets& assets) const = 0;
	virtual std::shared_ptr<IMiniMove> asPointner() const = 0;
};

