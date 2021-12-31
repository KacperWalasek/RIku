//
// Created by kamil-hp on 17.12.2021.
//

#ifndef RIKU_FRUSTUMCULLING_H
#define RIKU_FRUSTUMCULLING_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace front {
	struct Transform;

	struct Frustum {
		glm::mat4 projection, view;
		glm::vec3 ftl, ftr, fbr, fbl, ntl, ntr, nbr, nbl;
		bool isSphereOn(const glm::vec3& center, float radius,
		                 const Transform& modelTransform) const;
		Frustum(const front::Transform &camera, float aspect, float fov,
		                                float zNear, float zFar);
		Frustum()=default;
	};
}

#endif //RIKU_FRUSTUMCULLING_H
