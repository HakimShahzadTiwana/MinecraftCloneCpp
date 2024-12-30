#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader 
{
private:
	GLuint ID;

public:
	
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	void activate();
	void cleanUp();


private:
	std::string read_file_contents(const std::string& file);




};