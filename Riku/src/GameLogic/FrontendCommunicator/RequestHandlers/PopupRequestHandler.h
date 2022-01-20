#pragma once
#include "IRequestHandler.h"
class PopupRequestHandler :
    public IRequestHandler
{
public:
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

