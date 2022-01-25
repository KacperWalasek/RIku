#pragma once
#include "../GameLogic/FrontendCommunicator/Communicator.h"
#include "MiniGameState.h"
#include "MiniGameAssets.h"
#include "StateUpdate/MiniStateUpdate.h"
#include "MoveFactory/MiniMoveFactory.h"
#include "../GameLogic/IMiniGame.h"

namespace minigame
{
	class MiniGame : public IMiniGame
	{
		const int mapsize = 10;
		inline static MiniGameAssets assets;

		Communicator communicator;
		MiniStateUpdate stateUpdate;
		MiniGameState state;
		MiniMoveFactory factory;
	public:
		static MiniGameAssets& getAssets();

		MiniGame(const Unit& player, const Unit& enemy, bool begins);

		std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request) const;
		std::shared_ptr<IMove> makeMove(std::shared_ptr<IMoveDescription> moveDescription);
		bool isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const;

		void applyMiniPatch(std::shared_ptr<MiniPatch> patch);
		std::shared_ptr<MiniPatch> getCummulatedPatch() const;
		void resetCummulatedPatch();
	};

}