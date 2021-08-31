//
// Created by kamil-hp on 16.02.2021.
//

#ifndef GK_4_MODEL_H
#define GK_4_MODEL_H

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model {
public:
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh>    meshes;
	std::string directory;
	bool gammaCorrection;

	// constructor, expects a filepath to a 3D model.
	explicit Model(std::string const &path, float x_tex_scale=1.0f, float y_tex_scale=1.0f, bool gamma = false);

	// draws the model, and thus all its meshes
	void Draw(const Shader &shader, int index=0) const;

private:
	void loadModel(std::string const &path, float x_tex_scale=1.0f, float y_tex_scale=1.0f);
	void processNode(aiNode *node, const aiScene *scene, float x_tex_scale=1.0f, float y_tex_scale=1.0f);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene, float x_tex_scale=1.0f, float y_tex_scale=1.0f);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
	;
};


#endif //GK_4_MODEL_H
