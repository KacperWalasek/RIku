//
// Created by kamil-hp on 17.12.2021.
//

#include "FrustumCulling.h"
#include "Transform.h"
#include <iostream>

//from https://learnopengl.com/Guest-Articles/2021/Scene/Frustum-Culling by Six Jonathan

front::Frustum::Frustum(const front::Transform &camera, float aspect, float fov,
                                float zNear, float zFar) {
	projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
	view = camera.calculateViewMatrix();
	//init vertices
	glm::vec3 bl = getRelativeRay(projection, view, 0.0f, 0.0f);
	glm::vec3 br = getRelativeRay(projection, view, 1.0f, 0.0f);
	glm::vec3 tl = getRelativeRay(projection, view, 0.0f, 1.0f);
	glm::vec3 tr = getRelativeRay(projection, view, 1.0f, 1.0f);
	//set values
	nbl = bl * zNear;
	nbr = br * zNear;
	ntl = tl * zNear;
	ntr = tr * zNear;
	fbl = bl * zFar;
	fbr = br * zFar;
	ftl = tl * zFar;
	ftr = tr * zFar;

}

bool front::Frustum::isSphereOn(const glm::vec3& center, float radius, const front::Transform& transform) const
{
	return true;
}
