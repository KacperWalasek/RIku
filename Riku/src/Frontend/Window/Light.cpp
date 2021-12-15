#include "Light.h"

front::Light::Light()
{
	pointLightPositions = {
			glm::vec3(0.0f,  5.0f,  0.0f),
			glm::vec3(0.0f,  5.0f,  20.0f),
			glm::vec3(0.0f,  5.0f,  40.0f),
			glm::vec3(20.0f,  5.0f,  0.0f),
			glm::vec3(20.0f,  5.0f,  20.0f),
			glm::vec3(20.0f,  5.0f,  40.0f),
			glm::vec3(40.0f,  5.0f,  0.0f),
			glm::vec3(40.0f,  5.0f,  20.0f),
			glm::vec3(40.0f,  5.0f,  40.0f)
	};
}

front::Light::~Light()
{
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);
}

void front::Light::init()
{
	lightCubeShader.init("../shaders/light-vertex.shader", "../shaders/light-fragment.shader");

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void front::Light::apply(Shader& shader, float dayPart) const
{
	// directional light
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.03f + 0.3f * dayPart, 0.03f + 0.3f * dayPart, 0.03f + 0.3f * dayPart);
	shader.setVec3("dirLight.diffuse", 0.7f * dayPart, 0.7f * dayPart, 0.7f * dayPart);
	shader.setVec3("dirLight.specular", 0.9f * dayPart, 0.9f * dayPart, 0.9f * dayPart);

	// point lights
	for (int i = 0; i < pointLightPositions.size(); i++) {
		shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
		shader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.0f, 0.0f, 0.0f);
		shader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f * (1.0f - dayPart), 0.8f * (1.0f - dayPart), 0.8f * (1.0f - dayPart));
		shader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f * (1.0f - dayPart), 1.0f * (1.0f - dayPart), 1.0f * (1.0f - dayPart));
		shader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
		shader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
		shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032);
	}
	// spotLight
	float tmp_angle2 = glm::radians(spotLightAngle);
	for (int i = 0; i < numberOfSpotlights; i++) {
		shader.setVec3("spotLights[" + std::to_string(i) + "].position", glm::vec3({ 0.0f,1.7f,0.0f }));
		shader.setVec3("spotLights[" + std::to_string(i) + "].direction", glm::vec3(std::sin(tmp_angle2), 0.0f, std::cos(tmp_angle2)));
		shader.setVec3("spotLights[" + std::to_string(i) + "].ambient", 0.0f, 0.0f, 0.0f);
		shader.setVec3("spotLights[" + std::to_string(i) + "].diffuse", 1.0f, 1.0f, 1.0f);
		shader.setVec3("spotLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
		shader.setFloat("spotLights[" + std::to_string(i) + "].constant", 1.0f);
		shader.setFloat("spotLights[" + std::to_string(i) + "].linear", 0.09);
		shader.setFloat("spotLights[" + std::to_string(i) + "].quadratic", 0.032);
		shader.setFloat("spotLights[" + std::to_string(i) + "].cutOff", glm::cos(glm::radians(12.5f)));
		shader.setFloat("spotLights[" + std::to_string(i) + "].outerCutOff", glm::cos(glm::radians(15.0f)));
	}
}

void front::Light::drawCubes(glm::mat4 projection, glm::mat4 view, float fogDensity, glm::vec3 cameraPosition)
{
	lightCubeShader.use();
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);

	lightCubeShader.setFloat("fog_density", fogDensity);
	lightCubeShader.setVec4("fog_color", 0.5f, 0.5f, 0.5f, 1.0f);
	lightCubeShader.setVec3("camera_position", cameraPosition);

	//set night value
	lightCubeShader.setVec4("color", 1.0f, 1.0f, 1.0f, 1.0f);
	// we now draw as many light bulbs as we have point lights.
	glBindVertexArray(lightCubeVAO);
	for (unsigned int i = 0; i < pointLightPositions.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		lightCubeShader.setMat4("model", model);
		glm::mat4 inv_model = glm::mat4(1.0f);
		inv_model = glm::inverse(model);
		inv_model = glm::transpose(inv_model);
		lightCubeShader.setMat4("ti_model", inv_model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
