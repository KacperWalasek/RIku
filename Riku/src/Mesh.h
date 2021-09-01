//
// Created by kamil-hp on 16.02.2021.
//

#ifndef GK_4_MESH_H
#define GK_4_MESH_H

#include <vector>
#include <glm/glm.hpp>
class Texture;
class Shader;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

class Mesh {
public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	void Draw(const Shader &shader) const;
private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};


#endif //GK_4_MESH_H
