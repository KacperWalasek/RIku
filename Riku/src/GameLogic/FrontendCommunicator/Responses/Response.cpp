//Kacper Walasek
#include "Response.h"

Response::Response(std::shared_ptr<Request> request, bool status) : request(request), status(status)
{}

bool Response::getStatus() const
{
    return status;
}
