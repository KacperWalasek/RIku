//
// Created by kamil-xkom on 08.12.2021.
//

#ifndef RIKU_OBJECTDRAWMANAGER_H
#define RIKU_OBJECTDRAWMANAGER_H
#include <vector>
#include "DrawObject.h"

struct Shader;
namespace front {
    class Scene;
    class ObjectDrawManager {
        static std::vector<DrawObject> meshes;
    public:
        static void draw(Shader& shader, const Scene& scene);
        static void add(Object& object, glm::vec4 color={1.0,1.0,1.0,1.0});
    };
}


#endif //RIKU_OBJECTDRAWMANAGER_H
