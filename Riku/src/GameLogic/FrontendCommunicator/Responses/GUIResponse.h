#pragma once
#include "Response.h"
#include <vector>
class GUIResponse :
    public Response
{
    std::vector<std::vector<std::string>> options;
    std::vector<std::string> headers;
public:
    GUIResponse(std::shared_ptr<Request> request, std::vector<std::vector<std::string>> options, std::vector<std::string> headers)
        :Response(request, true), options(options), headers(headers)
    {}
    std::vector<std::vector<std::string>> getOption() { return options; }
    std::vector<std::string> getHeaders() { return headers; }

};

