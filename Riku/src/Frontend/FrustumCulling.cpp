//
// Created by kamil-hp on 17.12.2021.
//

#include "FrustumCulling.h"
#include "Transform.h"
#include "Util.h"
#include <iostream>
#include <array>

//from https://learnopengl.com/Guest-Articles/2021/Scene/Frustum-Culling by Six Jonathan

front::Frustum::Frustum(const front::Transform &camera, float aspect, float fov,
                                float zNear, float zFar): camera(&camera), zNear(zNear), zFar(zFar), aspect(aspect), fov(fov) {
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
	updateAngles();
}

std::array<glm::vec3, 3> getVectors(const front::Transform& transform) {
	return {front::rotate({1.0f, 0.0f, 0.0f}, transform.rotation),
		front::rotate({0.0f, 1.0f, 0.0f}, transform.rotation),
		front::rotate({0.0f, 0.0f, -1.0f}, transform.rotation)};
}

bool front::Frustum::isSphereOn(const glm::vec3& center, float radius, const front::Transform& transform) const
{
	glm::vec3 pos = transform.CalculateRelativePosition(center);
	/*float sd = sqrDistance(pos,camera.position);
	if(sd>=(zFar+radius)*(zFar+radius) || sd<std::max(zNear-radius,.0f)*std::max(zNear-radius,.0f))
		return false; //wrong distance test
	if(sd<0.01f) //if distance very small and radius>zNear, it should be included
		return true;
	auto cref = getVectors(camera);*/

	auto cameraVectors = getVectors(*camera);

	float d;
	float az,ax,ay;
	bool isIntersect=false;

	glm::vec3 v = pos-camera->position;

	az = glm::dot(v,-cameraVectors[2]);
	if (az > zFar + radius || az < zNear-radius)
		return false;

	if (az > zFar - radius || az < zNear+radius)
		isIntersect=true;

	ay = glm::dot(v,cameraVectors[1]);
	d = sphereFactorY * radius;
	az *= tang;
	if (ay > az+d || ay < -az-d)
		return false;

	if (ay > az-d || ay < -az+d)
		isIntersect=true;

	ax = glm::dot(v,cameraVectors[0]);
	az *= aspect;
	d = sphereFactorX * radius;
	if (ax > az+d || ax < -az-d)
		return false;

	if (ax > az-d || ax < -az+d)
		isIntersect=true;

	return true; //isIntersect
}

void front::Frustum::updateAngles() {
	// compute width and height of the near and far plane sections
	tang = std::tan(glm::radians(fov));
	sphereFactorY = 1.0f/std::cos(glm::radians(fov));

	// compute half of the the horizontal field of view and sphereFactorX
	float anglex = std::atan(tang*aspect);
	sphereFactorX = 1.0f/std::cos(anglex);
}
