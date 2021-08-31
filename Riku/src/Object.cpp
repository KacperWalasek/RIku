//
// Created by kamil-hp on 18.02.2021.
//

#include <iostream>
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"
#include "Shader.h"

const Transform Transform::Default=Transform();

Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sc): position(pos), rotation(rot), scale(sc) {}

glm::mat4 Transform::CalculateMatrix(const Transform &relativeTo) const {
	glm::mat4 ret=glm::mat4(1.0f);
	//set relativeTo
	ret=glm::translate(ret,relativeTo.position);
	ret=glm::scale(ret,relativeTo.scale);
	ret=glm::rotate(ret,glm::radians(relativeTo.rotation.x),glm::vec3(1.0f, 0.0f, 0.0f));
	ret=glm::rotate(ret,glm::radians(relativeTo.rotation.y),glm::vec3(0.0f, 1.0f, 0.0f));
	ret=glm::rotate(ret,glm::radians(relativeTo.rotation.z),glm::vec3(0.0f, 0.0f, 1.0f));
	//set this transform
	ret=glm::translate(ret,position);
	ret=glm::scale(ret,scale);
	ret=glm::rotate(ret,glm::radians(rotation.x),glm::vec3(1.0f, 0.0f, 0.0f));
	ret=glm::rotate(ret,glm::radians(rotation.y),glm::vec3(0.0f, 1.0f, 0.0f));
	ret=glm::rotate(ret,glm::radians(rotation.z),glm::vec3(0.0f, 0.0f, 1.0f));
	return ret;
}

glm::vec3 Transform::CalculateRelativePosition(const glm::vec3 &pos) const
{
	float C=cos(glm::radians(rotation.z));
	float S=sin(glm::radians(rotation.z));
	glm::vec3 ret;
	ret.x=position.x+(pos.x*C+pos.z*S);
	ret.y=position.y+pos.y;
	ret.z=position.z+(-pos.x*S+pos.z*C);
	return ret;
}
glm::vec3 Transform::CalculateRelativeFront(const glm::vec3 &pos) const
{
	float C=cos(glm::radians(rotation.z));
	float S=sin(glm::radians(rotation.z));
	glm::vec3 ret;
	ret.x=pos.x*C+pos.z*S;
	ret.y=0.0f;
	ret.z=-pos.x*S+pos.z*C;
	return ret;
}

void Object::Draw(const Shader &shader, int index) const {
	if(!IsSetModel())
	{
		std::cerr << "ERROR: Model not set";
		throw std::exception();
	}
	glm::mat4 mat_model = glm::mat4(1.0f);
	if(IsSetParent())
		mat_model=transform.CalculateMatrix(*parent);
	else
		mat_model=transform.CalculateMatrix();
	glm::mat4 inv_model = glm::mat4(1.0f);
	inv_model = glm::inverse(mat_model);
	inv_model = glm::transpose(inv_model);
	shader.setMat4("model", mat_model);
	shader.setMat4("ti_model", inv_model);
	//drawing
	model->Draw(shader, index);
}

Object::Object(const Model& model, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc): transform(pos, rot, sc){
	this->model=&model;
}
Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc): transform(pos, rot, sc){
	this->model=nullptr;
}
