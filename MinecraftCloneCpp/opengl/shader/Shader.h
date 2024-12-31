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

	// Helpers to set uniform type data in shaders
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void set3FloatVector(const std::string& name, float f1, float f2, float f3) const;


private:
	std::string read_file_contents(const std::string& file);

};
