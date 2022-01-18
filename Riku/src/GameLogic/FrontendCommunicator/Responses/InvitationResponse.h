#pragma once
#include <memory>
#include "../Requests/Request.h"
#include "Response.h"
#include <map>
#include "../../Utils/Invitation.h"

class InvitationResponse : public Response
{
    const std::map<std::string, Invitation>& response;
public:
    InvitationResponse(std::shared_ptr<Request> request, const std::map<std::string, Invitation>& response) : Response(request, true), response(response) {};
    std::map<std::string, Invitation> get() { return response; }
};

