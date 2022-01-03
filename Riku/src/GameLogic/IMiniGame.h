#pragma once

class MiniPatch;
class IMoveDescription;
class IMove;
class Response;
class Request;
class IMiniGame
{
public:
	virtual std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request) const = 0;
	virtual std::shared_ptr<IMove> makeMove(std::shared_ptr<IMoveDescription> moveDescription) = 0;
	virtual bool isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const = 0;

	virtual void applyMiniPatch(std::shared_ptr<MiniPatch> patch) = 0;
	virtual std::shared_ptr<MiniPatch> getCummulatedPatch() const = 0;
	virtual void resetCummulatedPatch() = 0;
};

