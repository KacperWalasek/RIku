//Kacper Walasek
#include "Response.h"

Response::Response(std::shared_ptr<Request> request, bool status) : status(status), request(std::move(request))
{}

bool Response::getStatus() const
{
    return status;
}
