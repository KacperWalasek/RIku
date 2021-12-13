//
// Created by kamil-hp on 18.02.2021.
//

#include <iostream>
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Model.h"
#include "Shader.h"

void front::Object::Draw(const Shader &shader, int index) const{
	if(!IsSetModel()) {
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

front::Object::Object(const Model& model, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc): model(&model), transform(pos, rot, sc) {}

front::Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 sc): model(nullptr), transform(pos, rot, sc) {}
