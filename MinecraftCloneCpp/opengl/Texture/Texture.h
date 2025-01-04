#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>

class Texture 
{
public:
	Texture(const std::string& texPath, bool bFlipped = false);
	~Texture() {};

	void bind();
	void unbind();

	// Sets this texture as active at the specified slot
	// You can have 16 or more active textures at a time depending on your gpu.
	void setActiveTexture(int activeTextureSlot);



private:
	GLuint ID;
};