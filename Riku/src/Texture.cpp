//
// Created by kamil-hp on 10.02.2021.
//

#include "Texture.h"
#include <GL/glew.h>
#include "stb_image.h"
#include <filesystem>
#include <iostream>

Texture::Texture(const std::string& type, const std::string& path, const std::string& dir, GLenum widthWrapping, GLenum heightWrapping) {
	if(!type.empty())
		init(type, path, dir, widthWrapping, heightWrapping);
}

void Texture::init(const std::string& type, const std::string& path, const std::string& dir, GLenum widthWrapping, GLenum heightWrapping) {
	this->path=path;
	this->type=type;
	std::string dir_tmp=dir;
	std::string path_tmp=path;
	glGenTextures(1, &ID);
		dir_tmp = std::filesystem::current_path().parent_path().string() + "/" + dir;
		for(int i=0;i<path_tmp.size();i++)
		{
			if(path_tmp[i] == '\\')
				path_tmp[i]='/';
		}
	// load image, create texture and generate mipmaps
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load((dir_tmp+"/"+path_tmp).c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if(nrChannels==1)
			format=GL_RED;
		else if(nrChannels == 3)
			format=GL_RGB;
		else if(nrChannels == 4)
			format=GL_RGBA;
		else
			format=GL_RED;
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, widthWrapping);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, heightWrapping);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		std::cout << "Texture from path: " << path << " loaded successfully with ID=" << ID << "\n";
	}
	else
	{
		std::cerr << "Failed to load texture at path:\n" << dir_tmp+"/"+path << "\n";
	}
	stbi_image_free(data);
}
