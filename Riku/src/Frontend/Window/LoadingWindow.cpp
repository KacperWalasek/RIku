#include "LoadingWindow.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"
#include <iostream>

LoadingWindow::LoadingWindow()
{
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	window = glfwCreateWindow(400, 200, "Riku", nullptr, nullptr); 
	if (window == nullptr) {
		std::cerr << "Creating loading window failed\n";
	}
	glfwMakeContextCurrent(window);
	shader.init("../shaders/loading-vertex.shader","../shaders/loading-fragment.shader");
	float vertices[] = {
			// positions                       // texture coords
			1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
			1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
			-1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// load and create a texture
	// -------------------------
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("../loading.png", &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if(nrChannels==1)
			format=GL_RED;
		else if(nrChannels == 3)
			format=GL_RGB;
		else if(nrChannels == 4)
			format=GL_RGBA;
		else
			format=GL_RED;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	shader.use(); // don't forget to activate/use the shader before setting uniforms!
	// or set it via the texture class
	shader.setInt("texture1", texture);
}

void LoadingWindow::destroy()
{
	glfwDestroyWindow(window);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void LoadingWindow::update()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// render container
	shader.use();
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

