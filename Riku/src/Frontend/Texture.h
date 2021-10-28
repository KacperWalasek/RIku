//
// Created by kamil-hp on 10.02.2021.
//

#ifndef GK_4_TEXTURE_H
#define GK_4_TEXTURE_H
#include <string>
#include <climits>
#include <GL/glew.h>

class Texture {
	void init(const std::string& type = "", const std::string& path = "", const std::string& dir = "", GLenum widthWrapping = GL_REPEAT, GLenum heightWrapping = GL_REPEAT);
public:
	unsigned int ID;
	std::string type;
	std::string path; // we store the path of the texture to compare with other textures
	int width;
	int height;
	int nrChannels;
	explicit Texture(const std::string& type="", const std::string& path="", const std::string& dir="", GLenum widthWrapping=GL_REPEAT, GLenum heightWrapping=GL_REPEAT);
};


#endif //GK_4_TEXTURE_H
