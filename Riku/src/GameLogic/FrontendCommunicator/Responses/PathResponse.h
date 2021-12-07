#pragma once
#include "Response.h"
#include <vector>
#include "../../Utils/Path.h"
class PathResponse :
    public Response
{
    Path path;
public:
    PathResponse(std::shared_ptr<Request> request, Path path)
        : Response(request, true), path(path) {}

    Path& get() { return path; }
};

