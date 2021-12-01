#pragma once
#include <vector>
#include <glm/gtx/rotate_vector.hpp>
#include "../Shader.h"
namespace front {
	class Light
	{
		int numberOfSpotlights = 1;
		std::vector<glm::vec3> pointLightPositions;

		float spotLightAngle = 0.0f;
		Shader lightCubeShader;
		unsigned int lightCubeVAO;
		unsigned int VBO;
	public:
		Light();
		~Light();
		void init();
		void apply(Shader& shader, float dayPart);
		void drawCubes(glm::mat4 projection, glm::mat4 view, float fogDensity, glm::vec3 cameraPosition);
	};
}

